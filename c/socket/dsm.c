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

#define BACK_LOG 10 // listen connection que size
#define SERVER_PORT 9000 // server port number 
#define MAX_HOSTNAME 50 // max hostname len 

/* start multiple process
 * using ssh to start cluster
 *
 */
// return the host ip address
char * get_host_ip(){
    char hostname[50]; // store local host name
    gethostname(hostname,sizeof(hostname));
    printf("[debug] server host name is: %s\n", hostname);
    struct hostent* ht = gethostbyname(hostname);
    if(! ht) printf("Error getting host name!\n");

    return inet_ntoa(*((struct in_addr *) ht->h_addr_list[0]));
}

int main() {
    int N = 3; // number of nodes to start
    pid_t pid; // process id of node
    
    // create a socket for the allocator to connect to the node  
    int server_socket = socket(AF_INET, SOCK_STREAM,0);

    // define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET; // IPV4
    server_address.sin_port = htons(SERVER_PORT); // bind only to port 9000
    server_address.sin_addr.s_addr = INADDR_ANY; // bind local address 

    // bind the socket to the specified IP and port
    bind(server_socket,(struct sockaddr*) &server_address, sizeof(server_address));
    listen(server_socket,BACK_LOG); // number specified that how many socket server can listen to

    for(int i = 0;i < N;++i){
        pid = fork();
        if (pid == 0) { // create a child process
            //close(server_socket);
            printf("I'm the child!\n");
            // remote start the node process with client excute exe with args
            system("ssh erikzhou@192.168.1.10 '/Users/erikzhou/Desktop/comp9243-asst1/share arg1 arg2'");

            //char *args[]={"./Hello","arg1","arg2",NULL};
            //execvp(args[0],args);
        } else if(pid < 0) { // faild to create the child process
            printf("Fail to create a child process!\n");
            exit(1);
        }
    }

    // listen to connections from the node once the node process has been remotely started



    for(int i =0 ; i< N;++i){
        wait(NULL);
    }

    return 0;
    
    
}
