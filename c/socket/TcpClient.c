#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>

int main() {
    // set up a TCP socket
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM,0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET; // TCP port
    server_address.sin_port = htons(9302); //port using host to internet short
    server_address.sin_addr.s_addr = INADDR_ANY; // connect to address is equiv to 0.0.0.0.0 
    
    // connect our socket to the server socket
    int connection_status = connect(network_socket,(struct sockaddr *) &server_address,
            sizeof(server_address));
    if(connection_status == -1) printf("Error with the connection\n"); 
    
    for(int i = 0; i< 3;++i){
        //send a message to the server    
        char client_message[] = "Hello from the client\n";
        send(network_socket,client_message,sizeof(client_message),0);
    
        // receive the data from the server into the buffer
        char server_response[256];
        recv(network_socket,&server_response,sizeof(server_response),0);
    
        // print the received message
        printf("Message Received %s\n",server_response);
    }

    close(network_socket);

    return 0;


} 

