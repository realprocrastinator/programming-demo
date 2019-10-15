// https://www.tutorialspoint.com/unix_sockets/socket_server_example.htm
#include <string.h>
#include<stdio.h>
#include<stdlib.h>
#include <limits.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<unistd.h>
#include <netdb.h>

#include<netinet/in.h>
#include<arpa/inet.h>

// processing and maitain connection with the client socket 
void processing(int client_socket){
    char client_message[256];
    while(1){
        recv(client_socket,client_message,sizeof(client_message),0);
        //if(client_message[0] == 'q') break;
        
        // send message to the client
        send(client_socket, client_message, sizeof(client_message),0);
    }
}

char * get_host_ip(){
    char hostname[50]; // store local host name
    gethostname(hostname,sizeof(hostname));
    printf("server host name is: %s\n", hostname);
    //printf("server address is: %u\n", server_address.sin_addr.s_addr);
    struct hostent* ht = gethostbyname(hostname);
    if(! ht) printf("Error getting host name!\n");

    return inet_ntoa(*((struct in_addr *) ht->h_addr_list[0]));
}

int main() {
    char server_message[256] = "You reached the server!\n";
    struct sockaddr their_addr; // connector's address informatio
    socklen_t addr_size = sizeof(their_addr);

    // create the TCP server socket
    int server_socket = socket(AF_INET, SOCK_STREAM,0);

    // define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9302); // bind only to port 9302
    server_address.sin_addr.s_addr = INADDR_ANY; // bind to any inbound address

    // bind the socket to the specified IP and port
    bind(server_socket,(struct sockaddr*) &server_address, sizeof(server_address));
    listen(server_socket,5); // number specified that how many socket server can listen to

    printf("server IP address is: %s\n",get_host_ip());
  
    while(1) {
        // accept connection from the client 
        int client_socket = accept(server_socket,&their_addr,&addr_size);
        // print the accepted connection info from the client
        char s[INET6_ADDRSTRLEN];
        inet_ntop(their_addr.sa_family, their_addr.sa_data,s, sizeof(s));
        printf("server: got connection from %s port: %d\n", s,
                ((struct sockaddr_in*) &their_addr)->sin_port);
        
        int pid = fork(); // create a new process after connection
        if(pid <0) {
            printf("Error creating new process!\n");
            exit(1);  
        }
        
        // each forked process will process and maitain connection with the client
        // until signal to exit
        if(pid == 0){ // the forked child process
            close(server_socket); // child process does not need t listen
            processing(client_socket);
            exit(0);
        } 

        // parent process will keep accpeting comming connection
        printf("[debug] received another connection!\n");
        close(client_socket); // parent does not need it
    }

    close(server_socket);

    return 0;
}





