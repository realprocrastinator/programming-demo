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
#define BUFFER_SIZE 256 // max number of client at the same time



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
    /*
    // set scoekt to async socket
    fcntl(network_socket, F_SETFL, O_ASYNC); 
    fcntl(network_socket, F_SETOWN,getpid()); 

    // catch SIGIO signal
    struct sigaction sa;
    sigset_t maskIO;
    sigset_t maskBlock;
    sigfillset(&maskBlock);
    sigaddset(&maskIO,SIGIO); // add IO sig to the mask set

    sa.sa_handler = asyncHandle;
    sa.sa_flags = SA_RESTART;
    sigfillset(&sa.sa_mask);
    //sigemptyset(&sa.sa_mask);
    sigdelset(&sa.sa_mask,SIGINT); // add IO sig to the mask set
    //sigprocmask(SIG_SETMASK,&maskBlock,NULL); // block all signals

    sigaction(SIGIO, &sa, NULL);	      // set the signal handler... 
    */
    //------------------------------------------------------------ 
    //send a message to the server    
    char client_message[BUFFER_SIZE];
    sprintf(client_message,"The Message");
    //send_flag = 1;
    // send will send very fast and receiver will receive the combine message as one 
    send(network_socket,client_message,strlen(client_message),0);
    //sleep(5);
    //pause(); // wait until there is IO and handle then continue
    char recv_buff[BUFFER_SIZE];
    recv(network_socket,recv_buff,sizeof(recv_buff),0);
    printf("client received %s\n",recv_buff);


    //for(int i =0;i< 3;++i) receiveMsg();

    //for(;;);
    close(network_socket);

    return 0;


} 

