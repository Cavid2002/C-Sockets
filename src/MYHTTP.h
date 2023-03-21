#include"MYNET.h"
#define Q_SIZE 10

unsigned int cln_fd;

typedef struct{
    unsigned int ip_family;
    unsigned int trcp_protocol;
    unsigned short port;
    unsigned short q_size;
    unsigned int listening_fd;
    unsigned int client_fd;
} http_server;

typedef struct{
    const char* filename;
    const char* method;
    const char* path;
}route;


void server_init(http_server* serv);

