#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <errno.h> 
#include <signal.h>
#include <sys/types.h>
#include <sys/mman.h>

int pagesize;
char* mem;

void segv_handler (int signum, siginfo_t *si, void *ctx){
  /* allow read access to mmap()ed area
   */
  printf("in the handler with errno: %d\n",si->si_errno);
  if (mprotect (mem, pagesize, PROT_READ))
    perror ("mprotect");

  /* after this, the signal handler will return and the offending statement
   * will be executed again
   */
}

int main(void){
    pagesize = getpagesize();
    mem = mmap (0, pagesize,
          PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS,-1,0);
    

    // pointer to the begining of the memeory
    struct sigaction sa;
    sa.sa_sigaction = segv_handler;
    sa.sa_flags = SA_RESTART;// after call the system call will restart the process can be 0
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGSEGV, &sa, NULL) == -1) { 
        perror("sigaction");
        exit(1);
    }

    mem[10] = 'A';
    if (mprotect (mem, pagesize, PROT_NONE))
        perror ("mprotect good");

    printf("The char is:%c\n",mem[10]); // access mode not allowed


    return 0; 
}
