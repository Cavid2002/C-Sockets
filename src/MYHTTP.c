#include"MYHTTP.h"
#define BUFF_SIZE 500

unsigned int cln_fd;

route* arr[4];
int count = 0;


void create_route(route* rt){
    char* buff[BUFF_SIZE];
    sprintf(buff, "HTTP/1.0 OK 200 %s",rt->method);
    FILE* html = fopen(rt->filename, "r");
    if(html == NULL){
        error("File doesn't exist");
    }    
    char temp[100];
    while(fgets(temp, 100, html) != NULL){
        strcat(buff, temp);
    }
    write(cln_fd,buff,strlen(buff));
    close(cln_fd);
    arr[count] = rt;
    count++;
}


void server_init(http_server* serv){
    serv->listening_fd = create_socket(serv->ip_family, serv->trcp_protocol);
    bind_to_port(serv->listening_fd,serv->ip_family,serv->port);
    start_listening(serv->listening_fd, serv->q_size);
    while(1){
        cln_fd = accept_connection(serv->listening_fd);
    }
}


int main(){
    route r1 = {.filename = "html/index.html",.method = "GET", .path="/test"};
    route r2 = {.filename = "html/index2.html",.method = "GET", .path="/test2"};
    route r3 = {.filename = "html/index3.html",.method = "GET", .path="/test3"};
    create_route(&r1);
    create_route(&r2);
    create_route(&r3);

    
}