
// pipe
// -FIFO byte stream, no way lseek() random access
// -Reader can specify how many bytes to read regardless how many bytes 
// writer write
/* -When the process read the bytes from the pipe message will be consumed
 * -When process read a empty pipe it will block until some bytes are written
 *  into the pipe
 * -Avoid two process read from the same pipe at the same time ,which would
 *  result one process read some bytes and other process the rest,each process
 *  will have incomplete information
 *
 *  -when a process try to write to a pipe that is full, write(2) will block until
 *  there is space to write in the pipe(4096 bytes buffer ,each byte write atomic)
 *
 * -if write end of the pipe close and other process try to read, will return 0
 */

/*
*  Video Lecture: 26
*  Programmer: Arif Butt
*  Course: System Programming with Linux
*  Bidirectional communication using two pipes between two related processes
*  Parent writes first and child reads
*  Child writes later and parent reads
*/
/* --------------------------------------------------------
 *pipe e.g.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define SIZE 1024
int main(){
    int fd1[2];
    int fd2[2];
    pipe(fd1);
    pipe(fd2);
    //create a child process
    pid_t cpid = fork();
    //***Child will read from fd2[0] and write into fd1[1]
    if (cpid == 0) {
       close(fd1[0]);
       close(fd2[1]);
       char childbuff[SIZE];
       memset(childbuff, '\0',SIZE);
       const char *msgfromchild = "Zalaid Mujahid Butt";
       //child receives a message from parent
       int n = read(fd2[0],childbuff,SIZE);
       printf("\nI am child.");
       printf("\nParent asked: ");
       fflush(stdout);
       write(1,childbuff,n);
       //child sends a response to parent
       write(fd1[1],msgfromchild,strlen(msgfromchild));
       exit(0);
    }
    //***Parent will write into fd2[1] and read from fd1[0]
    else {
       close(fd1[1]);
       close(fd2[0]);
       char parentbuff[SIZE];
       memset(parentbuff, '\0',SIZE);
       const char * msgfromparent = "What is your name child?";
       //parent sends a message to child
       write(fd2[1], msgfromparent,strlen(msgfromparent));
       //parent receives a message from child
       int n = read(fd1[0],parentbuff,SIZE);
       printf("\n\nI am parent, and have received my child's name.");
       printf("\nWelcome Mr. ");
       fflush(stdout);
       write(1,parentbuff,n);
       printf("\n");
 	  exit(0);
    }
}

//pipe e.g. end
// --------------------------------------------------------
// sending message to a process
// if pid > 0 send sig to the pid
// if pid == 0,signal will be send to all process in the same 
// process group of the calling process including the calling process
// if pid = -1 will signal all process that this process has permission 
// except init
int kill(pid_t pid, int sig);
int raise(int sig); // send sign to the process itself 
void abort(); // terminate the calling process by raising SIGABRT 
// cause a process to sleep until receive a sig that either terminate it 
// or to call a signal handler
int pause(); 
// the os will send the calling process a special signal SIGALARM(14)
// after the given number of seconds
unsigned int alarm(unsigned int);




//===============================================================================
// singnal
// call this function so that the process will handle the single whenver the signal 
// comes it , it controls which signal to accpet and how to handle it
/*
 * Paraams:
 * ----------
 * sig: which signal to catch
 * act: control the behavior ofthe signal handler
 * oact: can be NULL, else return theo old signal handler info
 */
 //Returns:
 // 0 on success -1 on error
// async safe
// https://docs.oracle.com/cd/E19455-01/806-5257/gen-26/index.html
#include<signal.h>

int sigaction(int sig, const struct sigaction *act, struct sigaction *oact);

struct sigaction sa;
sa.sa_sigaction= sigHandler; // the signal handler function
sigfillset(&sa.sa_mask);     // set of signals to block during the handling
sa.sa_flags = SA_SIGINFO | SA_RESTART // flags to config the behavior of the handler

int sigemptyset(sigset_t *set);                   // set the mask set as empty
int sigfillset(sigset_t *set);                    // set the all the mask set
int sigaddset(sigset_t *set, int signum);         // add a signal to the mask set
int sigdelset(sigset_t *set, int signum);         // remove a signal from the mask set
int sigismember(const sigset_t *set, int signum); // tests whether signum is a member of set.

// change the current signal mask set in the current process
// how: decide the behavior of the sigmask
//      SIG_BLOCK : The set of blocked signals is the union of the current set and
//                  the set argument.
//      SIG_UNBLOCK: The signals in set are removed from the current set of blocked signals.
//      SIG_SETMASK: The set of blocked signals is set to the argument set
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);

// will replace the current process signal mask with the mask and suspend
// the process until a signal is caught and handled rturns, then till
// will restore the process's old mask atomically
int sigsuspend(const sigset_t* mask);

//equiv to 
sigprocmask(SIG_SETMASK, &mask,&prevMask);
pause();
sigprocmask(SIG_SETMASK, &prevMask,NULL);



// sa_flags:
// http://man7.org/linux/man-pages/man2/sigaction.2.html
//      SA_SIGINFO:The signal handler takes three arguments, not one
// Params:
// ------
// -sig: the sig number that cause this handler
// -info: pointer to the struct that contains more info about the sig
// - uncontext: This is a pointer to a ucontext_t structure, cast to void *.
//              The structure pointed to by this field contains signal context
//              information that was saved on the user-space stack by the kernel
//
//
// ----------------------------------------------------------------
void handler(int sig, siginfo_t *info, void *ucontext);
siginfo_t {
    int      si_signo;     /* Signal number */
    int      si_errno;     /* An errno value */
    int      si_code;      /* Signal code */
    int      si_trapno;    /* Trap number that caused
                              hardware-generated signal
                              (unused on most architectures) */
    pid_t    si_pid;       /* Sending process ID */
    uid_t    si_uid;       /* Real user ID of sending process */
    int      si_status;    /* Exit value or signal */
    clock_t  si_utime;     /* User time consumed */
    clock_t  si_stime;     /* System time consumed */
    sigval_t si_value;     /* Signal value */
    int      si_int;       /* POSIX.1b signal */
    void    *si_ptr;       /* POSIX.1b signal */
    int      si_overrun;   /* Timer overrun count;
                              POSIX.1b timers */
    int      si_timerid;   /* Timer ID; POSIX.1b timers */
    void    *si_addr;      /* Memory location which caused fault */
    long     si_band;      /* Band event (was int in
                              glibc 2.3.2 and earlier) */
    int      si_fd;        /* File descriptor */
    short    si_addr_lsb;  /* Least significant bit of address
                              (since Linux 2.6.32) */
    void    *si_lower;     /* Lower bound when address violation
                              occurred (since Linux 3.19) */
    void    *si_upper;     /* Upper bound when address violation
                              occurred (since Linux 3.19) */
    int      si_pkey;      /* Protection key on PTE that caused
                              fault (since Linux 4.6) */
    void    *si_call_addr; /* Address of system call instruction
                              (since Linux 3.5) */
    int      si_syscall;   /* Number of attempted system call
                              (since Linux 3.5) */
    unsigned int si_arch;  /* Architecture of attempted system call
                              (since Linux 3.5) */
}

typedef struct ucontext_t {
    struct ucontext_t *uc_link;
    sigset_t          uc_sigmask;
    stack_t           uc_stack;
    mcontext_t        uc_mcontext;
    ...
} ucontext_t;

// ----------------------------------------------------------------


// specify a new disposition for the signal
struct sigaction {
    void (*sa_handler)(int) // signal handler function
    sigset_t sa_mask        // set of signal to block while this one is being handled
    int sa_flags            // 0 or to modify the behavior of the handler 
    void (*sa_restorer)(void) // not for application use
}

// will return the remaining seconds of the previous alamrs set
int alarm(int);
// ----------------------------------------------------------------
// alarm e.g.
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(){
   int i = alarm(205);
   printf("i contains: %d\n", i);
   sleep(5);
   int j = alarm(10);
   printf("After alarm(10); j contains: %d\n", j);
   sleep(100);
   exit(0);
}



//===============================================================================
// memory file mapping
// we can put -1 for fd and 0 for off for anonymous mapping
/* Params:
 * -------
 *  -addr: This is the address we want the file mapped into 
 *  if NULL will let the OS choose it for you
 *  -len: the length of the data we want to map into memory.
 *  -prot: The “protection” argument allows you to specify what kind of access this process has to the memory mapped region.
 *  bitwise-ORd mixture of :PROT_READ, PROT_WRITE, and PROT_EXEC
 *  -flags: MAP_SHARED share your changes to the file with other processes,
 *         MAP_PRIVATE you set it to the latter, your process will get a copy 
 *                     of the mapped region, so any changes you make to it will not be reflected in the original file
 *
 *         MAP_FIXED: can be oxrded, meaning start mapping at the exact location in memmory given
 *         MAP_ANONYMOUS: the map is not backed by any file and its content is init to 0s
 *                        fd will be ignored or set to -1 , the off should be 0
 * -fd: file descriptor of the file
 * -off: This is the offset in the file that you want to start mapping from
 *  this must be a multiple of the virtual memory page size.
 *  Return:
 *  -------
 *  -1 on error or pointer to the start of the mapped data.
 */
// Anonymous memory mapping
// https://stackoverflow.com/questions/34042915/what-is-the-purpose-of-map-anonymous-flag-in-mmap-system-call
// Anonymous mappings are simply large, zero-filled blocks of memory ready for use.
// MAP_ANONYMOUS + MAP_PRIVATE: the main purpose of using this kind of mapping is to allocate a new zeroized memory
//
void *mmap(void *addr, size_t len, int prot, 
                       int flags, int fd, off_t off);

// ----------------------------------------------------------------
// mmap() anonymous share memeory e.g. start
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>


int v = 5;

int main() {
    int *shared_memory =mmap(NULL, PAGESIZE, 
                                PROT_READ | PPORT_WRITE,
                                MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *shared_memory = 34;

    if(fork() == 0) {
        *shared_memory = 15;
        v = 80;
    } else {
        wait(NULL);
    }

    printf("Not shared. %i\n",v);
    printf("Shared. %i\n",*shared_memory);

}



// mmap() anonymous share memeory e.g. end
// ----------------------------------------------------------------
// sync the changes to the file mapped in the memmory and write back to the file
// Params:
// -------
// -addr: the pointer returned from mmap()
// -len: length of mapping
// -flags: how the update should be performed
//          MS_ASYNC: Request update the returns immediately
//          MS_SYNC: Requet update and wait for it to complete
//          MS_INVALIDATE: Invalidate other mapping of the same file
// Return:
// -------
int msync(void *addr, size_t , len, int flags);

// unmap the previous mapped file
// when process exit or perform exec will automatically unmap
// close fd will not unmap the region
int munmap(void *addr, size_t len)

// ----------------------------------------------------------------
// mmap() e.g. start
int main(int argc, char* argv[]){
   int fd = open("f1.txt", O_RDWR);
   // Stretch the file size to the new size
   lseek(fd, 100, SEEK_END); 
   write(fd, "", 1);

   //get attributes of the file
   struct stat sbuff; // use to get the file size
   fstat(fd, &sbuff);
   int fsize = sbuff.st_size;

   //memory map the file
   char* filedata = mmap(NULL, fsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
   printf("Data of f1.txt that is mapped in memory is:\n%s", filedata);

   //now write something in the file (remember the cfo is at the end)
   char *newdata = "This is GR8\n";
   strcat(filedata, newdata);
   printf("New data in the memory mapped region is:\n%s", filedata);
   //sync it
   msync(filedata, fsize, MS_SYNC);
   munmap(filedata, fsize);
   close(fd);
   return 0;
}

// mmap() e.g. end
// ----------------------------------------------------------------
// changes the access protections for the calling process's
// memory pages containing any part of the address range in the interval
// [addr, addr+len-1].  addr must be aligned to a page boundary.
// prot flags:
//     PROT_NONE  The memory cannot be accessed at all.
//     PROT_READ  The memory can be read.
//     PROT_WRITE The memory can be modified.
//     PROT_EXEC  The memory can be executed.
// Return 0 on success else -1
#include <sys/mman.h>
int mprotect(void *addr, size_t len, int prot);


//===============================================================================
// ----------------------------------------------------------------
#include <unistd.h>
#include <fcntl.h>
// perform  one of the operations described by the cmd  on the open file descriptor fd.
// cmd:
//     F_SETFL: set the file status flag On Linux, this command can change 
//              only the O_APPEND,O_ASYNC, O_DIRECT, O_NOATIME, and O_NONBLOCK flags.
//     F_SETOWN: Set the process ID or process group ID that will receive SIGIO
//               and SIGURG signals for events on the file descriptor fd.
//     

int fcntl(int fd, int cmd, ... /* arg */ );

// set the socket as non blocking async socket will get SIGIO signal when
// there is IO even occurs in the socket
fcntl (sock, F_SETFL, O_ASYNC); 
// set the current process ID that will receive the SIGIO on the socket
fcntl (sock, F_SETOWN, getpid ())



// ----------------------------------------------------------------
// async socket 
// http://www.masterraghu.com/subjects/np/introduction/unix_network_programming_v1.3/ch25lev1sec2.html






// ----------------------------------------------------------------
