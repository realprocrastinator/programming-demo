/* Demonstrates how to get the fault address of a SEGV a la POSIX.1b, which
 * is supported in Linux since stable kernel version 2.4.
 *
 * Manuel M. T. Chakravarty, 2001
 */

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>


//#define ADDR  ((char *) 0xdeadbeef)
#define ADDR  (void *)0x10a40f000
#define PAGE_NUM 0xffff


void handler (int signum, siginfo_t *si, void *ctx)
{

  void *addr;
  if (SIGSEGV != signum) {
    printf ("Panic!");
    exit (1);
  }
  addr = si->si_addr;		  /* here we get the fault address */
  printf ("Caught a seg fault sig and the offending address is %p.\n",addr);
  //addr = mmap(ADDR,((int)PAGE_NUM)*getpagesize(),PROT_WRITE|PROT_READ, MAP_FIXED | MAP_PRIVATE| MAP_ANONYMOUS,-1,0);
  addr = mmap(ADDR,getpagesize(),PROT_WRITE|PROT_READ, MAP_FIXED | MAP_PRIVATE| MAP_ANONYMOUS,-1,0);
  if (MAP_FAILED == addr) perror("nmap");

  //exit (0);
}

int main (){
  struct sigaction sa;
  void *addr;

  sa.sa_sigaction = handler;
  sa.sa_flags     = SA_SIGINFO;
  sigemptyset (&sa.sa_mask);
  sigaction (SIGSEGV, &sa, NULL);	      /* set the signal handler... */
  //printf("%c\n",*ADDR); // try to read
  //addr = mmap(ADDR,getpagesize(),PROT_WRITE|PROT_READ, MAP_PRIVATE| MAP_ANONYMOUS,-1,0);
  //printf("Returned address :%p\n",addr);
    
  int result = munmap(ADDR,((int)PAGE_NUM)*getpagesize());
  if(result == -1) perror("mumap");

  addr = mmap(ADDR,getpagesize(),PROT_WRITE|PROT_READ, MAP_FIXED | MAP_PRIVATE| MAP_ANONYMOUS,-1,0);
  if (MAP_FAILED == addr) perror("nmap");

  *((int *)ADDR) = 1; 
  printf("%d Defref %d, address: %p\n",PAGE_NUM/65535 ,*((int*)ADDR),ADDR);

  munmap(ADDR,getpagesize());

  return 0; /* we'll never get here */
}
