#include"MYHTTP.h"

#define BUFF_SIZE 10000
#define REQ_SIZE 1000
#define ROUTE_SIZE 20

http_route* arr[ROUTE_SIZE];
int count = 0;

void create_route(http_route* rt){
    arr[count] = rt;
    count++;
}

int find_file_by_path(char* url_path){
    for(int i = 0; i < count; i++){
        if(strcmp(arr[i]->path, url_path) == 0){
            return i;
        }
    }
    return -1;
}

void fill_render_buffer(char* url_path, char* buff){
    char temp[100];
    memset(temp, 0, 100);
    memset(buff, 0, BUFF_SIZE);
    char* ptr = strchr(url_path, '.');
    if(ptr != NULL){
        sprintf(temp, "../templates%s", url_path);
        FILE* front = fopen(temp, "r");
        if(front == NULL){
            error("File doesn't exist");
        }
        strcpy(buff, "HTTP/2.0 200 OK\r\n\r\n"); 
        while(fgets(temp, 100, front) != NULL){
            strcat(buff, temp);
        }
        fclose(front);
    }
    else{
        int index = find_file_by_path(url_path);
        if(index == -1) return;
        sprintf(temp, "../templates/%s", arr[index]->filename);
        FILE* front = fopen(temp, "r");
        if(front == NULL){
            error("File doesn't exist");
        }
        strcpy(buff, "HTTP/2.0 200 OK\r\n\r\n"); 
        while(fgets(temp, 100, front) != NULL){
            strcat(buff, temp);
        }
        fclose(front);
    }
    
}

void create_response(int cln_fd , char* buff){  
    write(cln_fd,buff,strlen(buff)); 
    close(cln_fd);
}


char* read_request(int fd, char* request){
    int c = read(fd, request, REQ_SIZE);
    if(c == -1){
        error("Unable to read");
    }
    request[c] = '\0'; 
    fprintf(stdout, "[INFO]Request data:\n\n%s", request);
    char* ptr1 = strchr(request, '/');
    char* ptr2 = strchr(ptr1,' ');
    *ptr2 = '\0';
    fprintf(stdout, "[INFO]URL path: %s\n", ptr1);
    fprintf(stdout, "\n==================================\n");
    if(strcmp(ptr1, "/favicon.ico") == 0){
        return NULL;
    }
    return ptr1;
}

void server_init(http_server* serv){
    char* buff = (char*)malloc(BUFF_SIZE);
    char* request = (char*)malloc(REQ_SIZE);
    serv->listening_fd = create_socket(serv->ip_family, serv->trcp_protocol);
    listner_fd = serv->listening_fd;
    bind_to_port(serv->listening_fd, serv->ip_family, serv->port);
    start_listening(serv->listening_fd, serv->q_size);
    fprintf(stdout, "[INFO]Server is listning on port: 127.0.0.1:%d\n", serv->port);
    fflush(stdout);
    while(1){
        
        int cln_fd = accept_connection(serv->listening_fd);
        char* prt = read_request(cln_fd, request);
        if(prt == NULL) continue;
        fill_render_buffer(prt, buff);
        create_response(cln_fd, buff);
        
    }

    exit(EXIT_SUCCESS);
}


