#include"MYHTTP.h"
#define BUFF_SIZE 500
#define ROUTE_SIZE 4


unsigned int cln_fd;

http_route* arr[ROUTE_SIZE];
int count = 0;


void create_route(http_route* rt){
    arr[count] = rt;
    count++;
}

void create_response(http_route* rt){
    char* buff = malloc(BUFF_SIZE);
    char* temp = malloc(100);
    if(buff == NULL || temp == NULL){
        error("Unable to allocate memory");
    }
    strcpy(buff, "HTTP/1.0 200 OK\r\n\r\n");
    FILE* html = fopen(rt->filename, "r");
    if(html == NULL){
        error("File doesn't exist");
    }    
    while(fgets(temp, 100, html) != NULL){
        strcat(buff, temp);
    }
    printf("HERE\n");
    write(cln_fd,buff,strlen(buff));
    close(cln_fd);
    free(buff);
    free(temp);
}


int read_request(int fd){
    char request[30];
    int c = read(fd, request, 30);
    if(c == -1){
        error("Unable to read");
    }
    request[c] = '\0'; 
    char* ptr1 = strchr(request, '/');
    char* ptr2 = strchr(ptr1,' ');
    *ptr2 = '\0';

    for(int i = 0; i < ROUTE_SIZE; i++){
        if(strcmp(ptr1,arr[i]->path) == 0){
            return i;
        }
    }
    return -1;
}

void server_init(http_server* serv){
    serv->listening_fd = create_socket(serv->ip_family, serv->trcp_protocol);
    bind_to_port(serv->listening_fd,serv->ip_family,serv->port);
    start_listening(serv->listening_fd, serv->q_size);
    fprintf(stdout,"[INFO] Listing on port 127.0.0.1:%d \n", serv->port);
    fflush(stdout);
    while(1){
        cln_fd = accept_connection(serv->listening_fd);
        int index = read_request(cln_fd);
        create_response(arr[index]);
    }
}


int main(){

    http_server serv;
    serv.ip_family = AF_INET;
    serv.trcp_protocol = SOCK_STREAM;
    serv.q_size = 10;
    serv.port = 3340;


    http_route r1 = {.filename = "../html/index.html",.method = "GET", .path="/test"};
    http_route r2 = {.filename = "../html/index2.html",.method = "GET", .path="/test2"};
    http_route r3 = {.filename = "../html/index3.html",.method = "GET", .path="/test3"};
    create_route(&r1);
    create_route(&r2);
    create_route(&r3);

    server_init(&serv);
    
}