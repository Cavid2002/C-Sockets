
#include<sys/socket.h>
#include<arpa/inet.h>
#include<signal.h>
#include<unistd.h>


#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr_storage sockaddr_storage;

int listner_fd;

void error(const char* msg);

int create_socket(int domain, int type);

int bind_to_port(int fd, unsigned int family, unsigned short port);

int accept_connection(int fd);

int connect_to_port(int fd, int ip_family, unsigned short port, const char* ip_addr);