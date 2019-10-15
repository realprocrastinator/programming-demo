
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
 * e.g.
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

// singnal
// call this function so that the process will handle the single whenver the signal 
// comes it , it controls which signal to accpet and how to handle it
/* Paraams:
 * ----------
 * sig: which signal to catch
 * act: control the behavior ofthe signal handler
 * oact: can be NULL, else return theo old signal handler info
 */
int sigaction(int sig, const struct sigaction *act, struct sigaction *oact);

struct sigaction {
    sa_handler // signal handler function
    sa_mask    // set of signal to block while this one is being handled
    sa_flags   // 0 or to modify the behavior of the handler 
}
