#include"MYHTTP.h"
#define BUFF_SIZE 5000
#define ROUTE_SIZE 4


http_route* arr[ROUTE_SIZE];
int count = 0;


void create_route(http_route* rt){
    arr[count] = rt;
    count++;
}

void create_response(int cln_fd ,http_route* rt, char* buff){
    memset(buff, 0, BUFF_SIZE);
    char temp[100];
    if(buff == NULL || temp == NULL){
        error("Unable to allocate memory");
    }
    strcpy(buff, "HTTP/1.1 200 OK\r\n\r\nContent-Type: text/html\r\n\r\n heello");
    // FILE* html = fopen(rt->filename, "r");
    // if(html == NULL){
    //     error("File doesn't exist");
    // }    
    // while(fgets(temp, 100, html) != NULL){
    //     strcat(buff, temp);
    // }
    // printf("[INFO]Page size:%d\n",strlen(buff));
    write(cln_fd,buff,strlen(buff));
    // printf("%s\n",buff);
    // fclose(html);
    close(cln_fd);
}


int read_request(int fd){
    char request[20];
    int c = read(fd, request, 20);
    if(c == -1){
        error("Unable to read");
    }
    request[c] = '\0'; 
    fprintf(stdout, "%s\n", request);
    char* ptr1 = strchr(request, '/');
    char* ptr2 = strchr(ptr1,' ');
    *ptr2 = '\0';
    fprintf(stdout, "%s\n", ptr1);
    for(int i = 0; i < ROUTE_SIZE; i++){
        if(strcmp(ptr1,arr[i]->path) == 0){
            return i;
        }
    }
    return -1;
}

void server_init(http_server* serv){
    char* buff = malloc(BUFF_SIZE);
    serv->listening_fd = create_socket(serv->ip_family, serv->trcp_protocol);
    bind_to_port(serv->listening_fd,serv->ip_family,serv->port);
    start_listening(serv->listening_fd, serv->q_size);
    fprintf(stdout,"[INFO] Listing on port 127.0.0.1:%d\n", serv->port);
    fflush(stdout);
    while(1){
        int cln_fd = accept_connection(serv->listening_fd);
        int id = fork();
        if(id == 0){
            int index = read_request(cln_fd);
            if(index == -1) continue;    
            create_response(cln_fd, arr[index],buff);
            
            exit(EXIT_SUCCESS);
        }
        
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