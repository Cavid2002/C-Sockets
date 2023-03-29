#include"MYNET.h"
#define Q_SIZE 10
#define BUFF_SIZE 1000
#define REQ_SIZE 1000
#define ROUTE_SIZE 20


typedef struct{
    unsigned int ip_family;
    unsigned int trcp_protocol;
    unsigned short port;
    unsigned short q_size;
    unsigned int listening_fd;
} http_server;

typedef struct{
    const char* filename;
    const char* method;
    const char* path;
}http_route;


void server_init(http_server* serv);
void create_route(http_route* rt);
char* read_request(int fd, char* request);
void create_response(char* url_path, char* buff, int cln_fd);