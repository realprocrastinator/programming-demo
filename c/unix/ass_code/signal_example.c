/* Demonstrates how to change the protection on a memory mapped area as a
 * response to a SEGV.
 *
 * Manuel M. T. Chakravarty, 2001
 */

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/mman.h>

char *mm_mem;		/* address of memory mapped file */
int   pagesize;		/* system page size */

/* signal handler for SEGV
 */
void segv_handler (int signum, siginfo_t *si, void *ctx)
{
  /* allow read access to mmap()ed area
   */
  if (mprotect (mm_mem, pagesize, PROT_READ))
    perror ("mprotect");

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
  //sigaction (SIGSEGV, &sa, NULL);
  sigaction (10, &sa, NULL);

  /* allocate a single page of anonymous mmap()ed memory
   */
  mm_mem = mmap (0, pagesize, 
		 PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 
		 -1, 0);   /* anonymous mapping doesn't need a file desc */
  if (MAP_FAILED == mm_mem)
    perror ("mmap");

  /* write to mapped memory
   */
  mm_mem[10] = 'A';

  /* disallow any access to the mapped file
   */
  if (mprotect (mm_mem, pagesize, PROT_NONE))
    perror ("mprotect");

  /* this statement will lead to a segmentation violation (SEGV), as 
   * `mm_mem[10]' currently has PROT_NONE, but it will succeed
   * after the SEGV signal handler enables read access again
   */
  printf ("mm_mem = %p; mm_mem[10] = %d\n", mm_mem, mm_mem[10]);

  /* clean up
   */
  munmap (mm_mem, pagesize);

  return 0;
}
