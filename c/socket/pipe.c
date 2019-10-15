#include <string.h>
#include<stdio.h>
#include<stdlib.h>
#include <limits.h>
#include <errno.h> 

#include <sys/wait.h>
#include<sys/types.h>
#include<sys/socket.h>

#include<unistd.h>
#include <netdb.h>

#include<netinet/in.h>
#include<arpa/inet.h>



int main() {
        int pfds[2]; // for pipe read and write between parent the process
        int pfds2[2]; // for pipe read and write between parent the process
        char buff[30];
        char buff2[30];
        char buff3[20];
        pipe(pfds);
        pipe(pfds2);

        for(int i = 0; i< 4;++i) {
            int pid = fork(); // create a new process after connection
            if(pid <0) {
                printf("Error creating new process!\n");
                exit(1);
            }

            // each forked process will process and maitain connection with the client
            // until signal to exit
            if(pid == 0){ // the forked child process
                close(pfds[0]);
                close(pfds2[1]);

                write(pfds[1],"barr",5);
                write(pfds[1],"foo",5);
                read(pfds2[0], buff2, 5);
                printf("child recieved pipe msg: %s\n",buff2);
                exit(0);
            }
            
            int result;
            // parent node
            for(int i = 0; i< 2;++i){
                result = read(pfds[0], buff, 5);
                printf("[pipe] result: %d parent received pipe message:%s\n",result,buff);
            }

            if(i==3){
                write(pfds2[1], "barr", 5); // write  pipe message to the child
                write(pfds2[1], "barr", 5); // write  pipe message to the child
                write(pfds2[1], "barr", 5); // write  pipe message to the child
                write(pfds2[1], "barr", 5); // write  pipe message to the child
            }

        }

        wait(NULL);
        wait(NULL);
        wait(NULL);
        wait(NULL);
}
