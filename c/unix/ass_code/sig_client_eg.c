/* Demonstrates how to make a socket asynchronous, cause it to generate 
 * SIGPOLL, and register a handler for SIGPOLL. Run together with a standard 
 * TCP server.
 *
 * Ihor Kuz, 2015
 */

#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define HOSTNAME "localhost"
#define PORT 9243

void poll_handler (int signum)
{
  printf("got async poll signal: %d\n", signum);
}

void main(void)
{
  struct sockaddr_in socket_addr;
  struct hostent *host;
  int sock;
  int res;

  host = gethostbyname (HOSTNAME);
  sock = socket (AF_INET, SOCK_STREAM, 0);
  socket_addr.sin_family = AF_INET;
  socket_addr.sin_port = htons (PORT);
  socket_addr.sin_addr = *((struct in_addr *) host->h_addr_list[0]);
  bzero(&(socket_addr.sin_zero), 8);
  res = connect (sock, (struct sockaddr *) &socket_addr, sizeof (struct sockaddr));
  if (res == 0) {
    printf ("connected to %s:%d\n", inet_ntoa (socket_addr.sin_addr), ntohs (socket_addr.sin_port));
  } else {
    fprintf(stderr, "connection to %s:%d failed: %s\n", inet_ntoa (socket_addr.sin_addr), ntohs (socket_addr.sin_port), strerror(errno));
    exit(1);
  }

  /* enable SIGPOLL on the socket */

  fcntl (sock, F_SETFL, O_ASYNC);
  fcntl (sock, F_SETOWN, getpid ());
 
  /* register signal handler */

  struct sigaction sa;
  sa.sa_handler = poll_handler;
  sa.sa_flags   = 0;
  sigemptyset (&sa.sa_mask);
  sigaction (SIGPOLL, &sa, NULL);

  while (1) ;
}
