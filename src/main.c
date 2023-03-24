#include"MYHTTP.h"

void handler(int num){
    close(listner_fd);
    fprintf(stdout, "\n[INFO]Closing connection...\n");
    exit(EXIT_SUCCESS);
}

int main(){
    signal(SIGINT, handler);
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