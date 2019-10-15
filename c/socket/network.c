


// ---------------------------------------------------
// structs
#include<netinet/in.h>

struct addrinfo {
    int ai_flags;// AI_PASSIVE, AI_CANONNAME, etc.
    int ai_family;// AF_INET, AF_INET6, AF_UNSPEC
    int ai_socktype;// SOCK_STREAM, SOCK_DGRAM
    int ai_protocol;// use 0 for "any"
    size_t ai_addrlen;// size of ai_addr in bytes
    struct sockaddr *ai_addr; // struct sockaddr_in or _in6
    char *ai_canonname;// full canonical hostname
    struct addrinfo *ai_next;// linked list, next node
};

//sa_family AF_INET (IPv4) or AF_INET6 (IPv6) 
struct sockaddr {
    unsigned short sa_family; // address family, AF_xxx
    char sa_data[14]; // 14 bytes of protocol address
};

// (IPv4 only--see struct in6_addr for IPv6)
// Internet address (a structure for historical reasons)
struct in_addr {
    uint32_t s_addr; // that's a 32-bit int (4 bytes) };
}

// internet socket addreess struct to be used with IPV4
// a pointer to a struct sockaddr_in can be cast to
// a pointer to a struct sockaddr and vice-versa
struct sockaddr_in {
    short int sin_family; // Address family, AF_INET unsigned short int sin_port; // Port number
    //Finally, the sin_port must be in Network Byte Order (by using htons()!)
    unsigned short int sin_port; // Port number
    struct in_addr sin_addr; // Internet address
    // which is included to pad the structure to the length of a struct sockaddr
    unsigned char sin_zero[8]; 
};

// ---------------------------------------------------
// socket e.g
// domain is PF_INET or PF_INET6(IPV4 or IPV6)
// type is SOCK_STREAM or SOCK_DGRAM(TCP,UDP)
// protocol can be set to 0 to match the given type
// return socket descriptor for later reference or  -1 on error
int socket(int domain, int type, int protocol);


// ---------------------------------------------------
#include <sys/types.h> 
#include <sys/socket.h>

// bind a socket with a address and port s.t. it will listen to the inbound traffic
// sockfd: socket file descriptor
// my_addr: is a pointer to sockaddr, which contains IP and port
// addrlen: length of the socket address
// returns -1 if there is error and set errno to the error's value
int bind(int sockfd, struct sockaddr *my_addr, int addrlen);
int sockfd;
struct sockaddr_in my_addr;
sockfd = socket(PF_INET, SOCK_STREAM, 0);
my_addr.sin_family = AF_INET;
my_addr.sin_port = htons(MYPORT); // short, network byte order 
my_addr.sin_addr.s_addr = inet_addr("10.12.110.57"); // or INADDR_ANY to bind to local address
memset(my_addr.sin_zero, '\0', sizeof my_addr.sin_zero);

// e.g.
// modern way of doing things with getaddrinfo()
struct addrinfo hints, *res;
int sockfd;
// first, load up address structs with getaddrinfo():
memset(&hints, 0, sizeof hints);
hints.ai_family = AF_UNSPEC; // use IPv4 or IPv6, whichever hints.ai_socktype = SOCK_STREAM;
hints.ai_flags = AI_PASSIVE; // fill in my IP for me
getaddrinfo(NULL, "3490", &hints, &res);
// make a socket:
// (you should actually walk the "res" linked list and error-check!)
sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol); // bind it to the port we passed in to getaddrinfo():
bind(sockfd, res->ai_addr, res->ai_addrlen);



/*
 * -The accept() call is used by a server to accept a connection 
 * request from a client. When a connection is available, the socket 
 * created is ready for use to read data from the process that requested 
 * the connection. The call accepts the first connection on its queue of
 * pending connections for the given socket socket.
 *
 * -The accept() call creates a new socket descriptor with the same 
 * properties as socket and returns it to the caller. 
 *
 *- If the queue has no pending connection requests, 
 * accept() blocks the caller unless socket is in nonblocking mode. 
 *
 * -socket: the socket descriptor of the listening or accepting socket 
 * -address: The socket address of the connecting client that is filled in by accept()
 *  can be NULL if the caller is not interested in the client address
 * -address_len:sizeof(address)
 *
 */
int accept(int socket, struct sockaddr *address, int *address_len);


//connect the socket to another socket given socket address
//e.g.  “10.12.110.57” on port “23” (the standard telnet port.) 
// it'll return -1 on error and set the variable errno.
// when we call connect we only care about the remote port number we are connecting
// we dont care about our local port, the kernel will choose a local port for us and 
// the site we are connecting to will automaticaly get the info from us
int connect(int sockfd, struct sockaddr *serv_addr, int addrlen);


// specify which socket to listen to with the size of the que for connections(backlog)
// incomming connections are going to wait in the queue until it is accept() backlog is
// the size of the queue
// returns -1 and sets errno on error.
// we need to call bind() before we call listen() so that the server 
// is running on a specific port
int listen(int sockfd, int backlog);



/*
 *  someone far far away will try to connect() to your machine on a port 
 *  that you are listen()ing on.Their connection will be queued up waiting to be 
 *  accept()ed. You call accept() and you tell it to get the pending connection.
 *  It'll return to you a brand new socket file descriptor to use for this single connection!
 *  the new socket fd is for receving and sending message to the client while the old
 *  socket is still listening for incomming connections
*/

//- sockfd: is the listening socket fd
//-addr is a pointer to the local storage of struct sockaddr_storage
//where the incomming connection information will be stored i.e. host ip and port
//-addrlen is a local interger var tha should be set to sizeof(struct sockaddr_storage)
// accpet() will not put more than that many bytes into addr, but if shorter it will change
// the value of addrlen to reflect that
// returns -1 and sets errno if an error occurs
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

// e.g.
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h>
#define MYPORT "3490"  // the port users will be connecting to
#define BACKLOG 10     // how many pending connections queue will hold

int main(void) {
    struct sockaddr_storage their_addr; socklen_t addr_size;
    struct addrinfo hints, *res;
    int sockfd, new_fd;
    // !! don't forget your error checking for these calls !!

    // first, load up address structs with getaddrinfo():
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // use IPv4 or IPv6, whichever hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // fill in my IP for me
    getaddrinfo(NULL, MYPORT, &hints, &res);
    // make a socket, bind it, and listen on it:
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol); bind(sockfd, res->ai_addr, res->ai_addrlen);
    listen(sockfd, BACKLOG);
    // now accept an incoming connection:
    addr_size = sizeof their_addr;
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
    // ready to communicate on socket descriptor new_fd! .
    

}


//-sockfd: the socekt fd that you send data to
//-msg: pointer to the data that you want to send
//-len: lenght fo the data in bytes
//-flag: set to 0
// return -1 on error and errno is set to the error number
// return number of bytes sent and when data is big > 1K it probabily would not
// be able to send all data in one go ,so return sent number can be smaller
// that the data len you intend to send, it is up to the user to send the rest 
int send(int sockfd, const void *msg, int len, int flags);


//-sockfd: the socket fd that you read from
//-buff: buffer to read the info into
//-len: max lenght of the buffer
//-flag: can be set to 0
// returns -1 on error and errno is set to the error number
// returns number of byts actually read into the buffer
// return 0 means the remote side has closed the connection
int recv(int sockfd, void *buf, int len, int flags);

// prevents any more read and write to the socket
close(sockfd);


// returns the name of the computer that your program is running on.
// The name can then be used by gethostbyname()
// to determine the IP address of your local machine.
// returns 0 on successful completion, and -1 on error, setting errno as usual.
#include <unistd.h>
int gethostname(char *hostname, size_t size);

// give the host name will get the ip address of the host
#include <netdb.h>
struct hostent *gethostbyname(const char *name);

struct hostent {
    char  *h_name;            /* official name of host */
    char **h_aliases;         /* alias list */
    int    h_addrtype;        /* host address type */
    int    h_length;          /* length of address */
    char **h_addr_list;       /* list of addresses */
}


// given a socket fd that connected with will tell you who you gets connected to
// e.g. IP and port
// -sockfd: the socket fd that you want to check
// -addr: the socket address info relate to that socket
int getpeername(int sockfd, struct sockaddr *addr, int *addrlen);



//------------------------------------------------------------------------
// client server sample




