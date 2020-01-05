#include<stdio.h>
#include<stdlib.h>
#include<errno.h>  
#include<string.h>   //strlen  

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>
#include<unistd.h>   //close  
#include<arpa/inet.h>    //close  

#define PORT 8888  
#define MAX_CLIENT 30 // max number of client at the same time
#define BUFFER_SIZE 1024 // max number of client at the same time

/*
   Usage:
    start server
    telnet localhost 8888
*/

// ------------------------------------------------------------------------------
// Given a port number will create a TCP sever socket listening 
// on this port for incomming traffic
int tcpServerSock(int port){
    // create the TCP server socket
    int server_socket = socket(AF_INET, SOCK_STREAM,0);

    // define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port); // bind only to port 9302
    server_address.sin_addr.s_addr = INADDR_ANY; // bind to any inbound address

    // bind the socket to the specified IP and port
    bind(server_socket,(struct sockaddr*) &server_address, sizeof(server_address));
    listen(server_socket,5); // number specified that how many socket server can listen to

    printf("Server listener on port %d... \n", PORT);   

    return server_socket;
}
// ------------------------------------------------------------------------------
// when select return readfds will only contains the socket that has event
// need to reset to continue monitor the socket of interest
fd_set reMonitor(int server_socket,int* client_socket,fd_set readfds,int* max_sd){
    *max_sd = server_socket; // server socket is the first one and the largest
    int sd;

    FD_SET(server_socket,&readfds); // add server socket to moniter read
    for(int i =0;i<MAX_CLIENT;++i) {
        if((sd = client_socket[i]) > 0) FD_SET(sd,&readfds);
        if(sd > *max_sd) *max_sd = sd;
    } 

    return readfds;
}
// ------------------------------------------------------------------------------
// after server receive new connection from the client accepted the request handle connection
void handleConnection(int new_socket, struct sockaddr_in sock_address, int *client_socket){
    printf("New connection , socket fd is %d , ip is : %s , port : %d \n" 
        , new_socket , inet_ntoa(sock_address.sin_addr) , ntohs(sock_address.sin_port));   
    
    int i;
    for(i =0; client_socket[i] !=0;++i);
    client_socket[i] = new_socket;

}
// ------------------------------------------------------------------------------
// after client socket read to recieve message recieve and handle the message
void messageHandler(char* recv_buffer,int valread,int sd){
    // will receive: 1 readreply memory_contents_of_page
    // tokenise message
    char* pt = recv_buffer;
    int msg_len;
    char len_buff[5];

    
    while(valread > 0) {
        memcpy(len_buff,pt,1); // get messagelen
        sscanf(len_buff,"%d",&msg_len);

        memcpy(&msg_len,pt,sizeof(int)); // get messagelen
    
        char token_buff[1024];
        memcpy(token_buff,pt + sizeof(int),msg_len - sizeof(int));
    
        printf("get token %s\n",token_buff);
    
        pt = pt + msg_len;
        valread -= msg_len;

    }





    /*
    printf("[SERVER] receive message: %s with len: %d\n", recv_buffer,valread);
    char* msgs[256];
    int result = split(recv_buffer," ", msgs);


    printf("The header is:\n");
    for(int i = 0 ;i < result -1 ;++i) printf("%s\n",msgs[i]);

    printf("The page content is:\n");
    int* arry = (int *)msgs[result-1];
    for(int i = 0; i< 10;++i) printf("get num:%d\n",arry[i]);
    */





    send(sd,recv_buffer,strlen(recv_buffer),0);
}
// ------------------------------------------------------------------------------
// when detect a remote client socket closed ,close the client socket,
// remove the the socket from the client soeckt
void clientSockClose(int sd){
    struct sockaddr_in sock_address;
    int addrlen;

    getpeername(sd, (struct sockaddr*)&sock_address, 
            (socklen_t*)&addrlen);
    printf("Host disconnected , ip %s , port %d \n" ,  
          inet_ntoa(sock_address.sin_addr) , ntohs(sock_address.sin_port));   
    
    close(sd);
}
// ------------------------------------------------------------------------------
// split according to delim and will stop tokenise if second string is readreply,
// will not tokenise the remaining string after readreply
// special case in format: nid readreply content_of_page
int split(char* s, char* delim, char** result){
    int counter = 0;
    char* pch;
    int read_flag = 0;

    for(pch = strtok(s,delim);pch !=NULL;
            result[counter++] = pch, pch = strtok (NULL, delim)){
        if(!strcmp(pch,"readreply")) {
            read_flag = 1;
            break;
        }
    }
    if(read_flag){
        result[counter++] = pch;
        result[counter++] = pch + strlen(result[counter -1]) + 1;
    }
    return counter;
}


// ------------------------------------------------------------------------------
// ===========================================================================
int main() {
    int addrlen, new_socket, client_socket[MAX_CLIENT]={}, 
         max_sd,activity, sd;  
    fd_set readfds,exceptfds; // fd set for read and except
    char recv_buffer[BUFFER_SIZE] = {}; // buffer for receiving message from the client
    struct sockaddr_in sock_address; // for store client sock address
    //----------------------------------------------------------
    int server_socket = tcpServerSock(PORT); // creat tcp server socket listen on the port
    
    while(1) {
        // reset the socket of interest after select returns 
        FD_ZERO(&readfds); // clear the readfds
        readfds = reMonitor(server_socket,client_socket,readfds,&max_sd);

        // wait for event on the sockets that monitors
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        if(activity < 0 && errno != EINTR) printf("Select Error!\n"); // select error
        
        // if there is event on the server_socket, must be new client connection request 
        if(FD_ISSET(server_socket, &readfds)) {
            // accept the new connection and error handle
            if((new_socket = accept(server_socket,
                            (struct sockaddr *)&sock_address, (socklen_t*)&addrlen))< 0){
                perror("accept");
                exit(EXIT_FAILURE);
            } 
            // handle the connection
            handleConnection(new_socket, sock_address, client_socket); 
        }

        // loop through all client socket check if there is any IO event on the client socket
        for(int i = 0; i < MAX_CLIENT;++i){
            if(!client_socket[i]) continue; // no need to process empty socket

            int valread;
            memset(recv_buffer,'\0',sizeof(recv_buffer));
            if(FD_ISSET(sd = client_socket[i], &readfds)){
                // client socket closed
                if((valread = recv(sd, recv_buffer,sizeof(recv_buffer),0)) == 0){
                    clientSockClose(sd);
                    client_socket[i] = 0; // noe need to keep track
                // client socket alive and received message
                } else { 
                    printf("Actually read %d bytes\n",valread);
                    // handle the incomming message from the client
                    messageHandler(recv_buffer,valread,sd);
                }
            }
        }
    }


    
    close(server_socket);

    return 0;
}


