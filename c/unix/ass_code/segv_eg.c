/* Demonstrates how to change the protection on a memory mapped area as a
 * response to a SEGV.
 * Manuel M. T. Chakravarty, 2001
 */
#include<stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/mman.h>
#define ADDR  ((char *) 0x40000000)

char *mm_mem;		/* address of memory mapped file */
int   pagesize;		/* system page size */

/* signal handler for SEGV
 */
void segv_handler (int signum, siginfo_t *si, void *ctx)
{
  /* allow read access to mmap()ed area
   */
  printf ("Inside hadnler and the offending address is %p\n", si->si_addr);
  
  mm_mem = mmap (si->si_addr, getpagesize(), 
		 PROT_READ | PROT_WRITE, MAP_FIXED|MAP_PRIVATE | MAP_ANONYMOUS, 
		 -1, 0);   /* anonymous mapping doesn't need a file desc */
  
 // ((char*)si->si_addr)[10] ='A';
  mm_mem[10] ='A';
  printf("the char is :%c\n",mm_mem[10]);

  /* after this, the signal handler will return and the offending statement
   * will be executed again
   */
}

int main (int argc, char *argv[])
{
  struct sigaction sa;

  pagesize = getpagesize ();

  /* register SEGV signal handler
   */
  sa.sa_sigaction = segv_handler;
  sa.sa_flags     = SA_SIGINFO;
  sigemptyset (&sa.sa_mask);
  //sigaction (10, &sa, NULL);
  sigaction (SIGSEGV, &sa, NULL);

  /* allocate a single page of anonymous mmap()ed memory
  mm_mem = mmap (ADDR, pagesize, 
		 PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_FIXED | MAP_ANONYMOUS, 
		 -1, 0);    
  if (MAP_FAILED == mm_mem)
    perror ("mmap");

  munmap (mm_mem, pagesize);
   */
  /* write to mapped memory
   */
  ADDR[10] = 'A';

  printf("the char is :%c\n",ADDR[10]);
  /* disallow any access to the mapped file
   */
  int result = mprotect (mm_mem, pagesize, PROT_NONE);
  if (result)
    perror ("mprotect");

  printf("result is %d\n", result);
  /* this statement will lead to a segmentation violation (SEGV), as 
   * `mm_mem[10]' currently has PROT_NONE, but it will succeed
   * after the SEGV signal handler enables read access again
   */
  printf ("mm_mem = %p; mm_mem[10] = %c\n", mm_mem, mm_mem[10]);

  /* clean up
   */
  //munmap (mm_mem, pagesize);

  return 0;
}
