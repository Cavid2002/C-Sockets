#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>

int socket(int domain, int type, int protocol);

int bind(int socketfd, sockaddr* myaddr, socklen_t addrlen);

int listen(int socketfd,int backlog);

int accept(int socketfd, sockaddr* myaddr, socklen_t* addrlen);

int connect(int socketfd, sockaddr* myaddr, socklen_t addrlen);