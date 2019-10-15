#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h>

/* start multiple process
 * using ssh to start cluster
 *
 */

int main() {
    int N = 3;
    int status;
    pid_t pid;

    for(int i = 0;i < N;++i){
        pid = fork();
        if (pid == 0) { // create a child process
            printf("I'm the child!\n");
            // excute exe with args
            // system("ssh erikzhou@192.168.1.10 '/Users/erikzhou/Desktop/notes/c/Hello arg1 arg2'");
            sleep(2);

            //char *args[]={"./Hello","arg1","arg2",NULL};
            //execvp(args[0],args);
        } else if(pid < 0) { // faild to create the child process
            printf("Fail to create a child process!\n");
            exit(1);
        }
    }

    printf("I'm the parent!\n");
    printf("-------------------\n");
    wait(NULL);
    printf("first child exit!\n");
    wait(NULL);
    printf("second child exit!\n");
    wait(NULL);
    printf("all child exit!\n");
    
    
}
