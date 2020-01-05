#include<stdio.h>
#include<stdlib.h>
#include<errno.h>  
#include<string.h>   //strlen  

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>
#include<unistd.h>   //close  
#include<arpa/inet.h>    //close  

#include <fcntl.h>
#include <signal.h>

#define PORT 8888  



//------------------------------------------------------------------
//global varible
int send_flag = 0; // when send message
int network_socket; // socket connect to the server

void receiveMsg(){
   char server_response[256];
   memset(server_response,'\0',sizeof(server_response));
   int result =recv(network_socket,server_response,sizeof(server_response),0);
   
   // print the received message
   printf("%d Message Received: %s\n",result,server_response);
}

//------------------------------------------------------------------
void asyncHandle(int signum){
    printf("insde the handler send flag:%d\n",send_flag);
    if(send_flag){
        send_flag = 0;
        return;
    }
   char server_response[256];
   memset(server_response,'\0',sizeof(server_response));
   int result =recv(network_socket,server_response,sizeof(server_response),0);
   
   // print the received message
   printf("%d Message Received: %s\n",result,server_response);

}

#define PAGE_SIZE 100//(strlen("hello world")) 
#define BUFFER_SIZE 256

// ==================================================================
int main() {
    // set up a TCP socket
    network_socket = socket(AF_INET, SOCK_STREAM,0);
    
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET; // TCP port
    server_address.sin_port = htons(PORT); //port using host to internet short
    server_address.sin_addr.s_addr = INADDR_ANY; // connect to address is equiv to 0.0.0.0.0 
    
    // connect our socket to the server socket
    int connection_status = connect(network_socket,(struct sockaddr *) &server_address,
            sizeof(server_address));
    if(connection_status == -1) printf("Error with the connection\n"); 
   
    //------------------------------------------------------------ 
    char delim = '|';
    char *pt =(char *)malloc(PAGE_SIZE*sizeof(char));
    pt = "hello world"; 

    for(int i = 0; i< 3;++i){
        char* header = "1 2 addr readReply ";
        //(header + strlen(header)-1) = ' ';
        //char send_buff[strlen(header) + pagesize + 5];
        char send_buff[BUFFER_SIZE];
        memset(send_buff,0,sizeof(send_buff));
        memcpy(send_buff,header,strlen(header));
        memcpy(send_buff + strlen(header),pt,PAGE_SIZE);
    
        memcpy(send_buff + strlen(header) + PAGE_SIZE,&delim,1); // add token delimitor
        memcpy(send_buff + strlen(header) + PAGE_SIZE + 1,"3 write|",strlen("3 write|"));
    
        send(network_socket,send_buff,strlen(header) + PAGE_SIZE + strlen("3 write|") + 1 ,0);
        printf("client sending:%s:\n",send_buff);
    }

   close(network_socket);

    return 0;


} 

