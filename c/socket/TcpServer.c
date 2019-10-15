#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>


int main() {
    char server_message[256] = "You reached the server!\n";

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
   
    while(1) {
        // accept connection from the client 
        int client_socket = accept(server_socket,NULL,NULL);
        while(1) {
            char client_message[256];
            recv(client_socket,client_message,sizeof(client_message),0);
            //if(client_message[0] == 'q') break;

            // send message to the client
            send(client_socket, client_message, sizeof(client_message),0);
        }
    }

    close(server_socket);

    return 0;
}





