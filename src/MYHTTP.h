#include"MYNET.h"

#define Q_SIZE 10
#define BUFF_SIZE 1000
#define REQ_SIZE 100
#define PATH_SIZE 100
#define ROUTE_SIZE 20
#define METHOD_SIZE 10
#define GET 0
#define POST 1


typedef struct{
    unsigned int ip_family;
    unsigned int trcp_protocol;
    unsigned short port;
    unsigned short q_size;
    unsigned int listening_fd;
} http_server;

typedef struct{
    const char* filename;
    unsigned short method;
    const char* path;
}http_route;

typedef struct{
    char* path;
    char* request_data;
} http_request;


extern http_route* arr[ROUTE_SIZE];
extern int count;

void server_init(http_server* serv);
void create_route(http_route* rt);
void read_request(int fd, http_request* request, unsigned short* method);
void create_response(char* url_path, char* buff, int cln_fd);

