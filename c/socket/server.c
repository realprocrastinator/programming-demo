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



//---------------------------------------------------------------
// split according to delim and will stop tokenise if second string is readreply,
// will not tokenise the remaining string after readreply
// special case in format: nid readreply content_of_page
//char s = "register|exit|nid readreply page_contentnid write addr|"
int splitString(char* s, char* delim, char** result){
    int counter = 0;
    char* pch;
    int read_flag = 0;
    int pipe_flag = strcmp(delim,"|")? 0 :1;

    for(pch = strtok(s,delim);pch !=NULL;
            result[counter++] = pch, pch = strtok (NULL, delim)){

        if(!strcmp(pch,"readReply")) { // to process words for each message
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

//---------------------------------------------------------------

char* findChar(char* s,char delim,int len){
    for(int i = 0; i < len;++i) 
        if(*(s+i) == delim) return s + i;
    return NULL;
}

char* findNthChar(char* s, char delim, int len,int n){
    int count = 0;
    for(int i = 0; i < len;++i)
        if(*(s+i) == delim && ++count == n) return s + i;
    return NULL;
}


#define BUFFER_SIZE 256*10 // max number of client at the same time
//#define PAGE_SIZE 100//(strlen("page|content") - 1)
//#define PAGE_SIZE (strlen("hello world")) 
#define PAGE_SIZE 100//(strlen("hello world")) 
//---------------------------------------------------------------
int splitToken(char* s,char delim, char** result,int recv_len){
    char* ptBegin = s ,*ptEnd = s;
    int count = 0,len = recv_len;

    while((ptEnd = findChar(ptBegin,delim,len))){
        // spcecial case to exclude page special char conflict with delim
        // in format: nid readreply page|content here|nid write addr
        char *space_pt = findNthChar(ptBegin,' ',len,3); // find third space
        char *delim_pt = findChar(ptBegin,'|',len);

        // only consider when there is no token before the possible readreply;;
        if(delim_pt > space_pt && space_pt &&
                !strncmp(space_pt+1,"readReply", strlen("readReply"))){

            char *space_pt2 = findChar(space_pt + 1,' ',len); // find second space
            printf("fourth space:%s\n",space_pt2);
            // skip the space from second space acroos all page content and replace
            // the delimiter by the end of the page by string terminator
            ptEnd = space_pt2 + 1 + PAGE_SIZE;
        }

        *ptEnd = '\0'; // change delimiter to string terminator
        result[count++] = ptBegin; // mark this token
        len -= (ptEnd - ptBegin);
        ptBegin = ptEnd + 1; // move pt for the next token
    }

    return count;
}


// ------------------------------------------------------------------------------
// after client socket read to recieve message recieve and handle the message
void messageHandler(char* buffer,int recv_len,int sd){
    char recv_buffer[BUFFER_SIZE];
    memset(recv_buffer,'\0',sizeof(recv_buffer));
    memcpy(recv_buffer,buffer,recv_len);


    printf("Buffer content start -------------------------\n\n");
    for(int i =0;i<BUFFER_SIZE;++i){
        if(*(recv_buffer+i) =='\0') printf("0");       


        printf("%c",*(recv_buffer+i));
    }
    printf("\n\nBuffer content end -------------------------\n");

    printf("[SERVER] receive message:%s with len:%d\n", recv_buffer,recv_len);
    char* msgs[256];
    int token_len = splitToken(recv_buffer,'|', msgs,BUFFER_SIZE);
    //int token_len = splitString(recv_buffer,"|", msgs);

    for(int i = 0; i < token_len;++i){
        printf("[MSG] whole msg %d:%s\n",token_len,msgs[i]);
        char* msg[256];
        int msg_len = splitString(msgs[i]," ", msg);
        for(int i = 0;i< msg_len;++i) printf("msg %d:%s\n",msg_len,msg[i]);
    }


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
// ===========================================================================
int main() {
    int addrlen, new_socket, client_socket[MAX_CLIENT]={}, 
         max_sd,activity, sd;  
    fd_set readfds,exceptfds; // fd set for read and except
    char recv_buffer[BUFFER_SIZE]; // buffer for receiving message from the client
    memset(recv_buffer,'\0',sizeof(recv_buffer));

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


