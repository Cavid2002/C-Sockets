#include"MYHTTP.h"
#include<fcntl.h>
#include<sys/ioctl.h>

http_route* arr[ROUTE_SIZE];
int count = 0;

void handler(int num)
{
    close(listner_fd);
    fprintf(stdout, "\n[INFO]Closing connection...\n");
    exit(EXIT_SUCCESS);
}

void create_route(http_route* rt)
{
    arr[count] = rt;
    count++;
}

int find_file_by_path(char* url_path)
{
    for(int i = 0; i < count; i++){
        if(strcmp(arr[i]->path, url_path) == 0){
            return i;
        }
    }
    return -1;
}

void create_response(char* url_path, char* buff, int cln_fd)
{
    char temp[50];
    memset(temp, 0, 50);
    memset(buff, 0, BUFF_SIZE);

    char* ptr = strchr(url_path, '.');
    if(ptr != NULL)
    {
        sprintf(temp, "templates%s", url_path);
        int front_fd = open(temp, O_RDONLY, 0700);
        if(front_fd == -1){
            error("File doesn't exist");
        }
        strcpy(buff, "HTTP/2.0 200 OK\r\n\r\n");
        write(cln_fd, buff, strlen(buff));
        int c = 1;
        while(c > 0){
            c = read(front_fd , buff, BUFF_SIZE);
            write(cln_fd, buff, c);
        }
        close(front_fd);
    }
    else
    {
        int index = find_file_by_path(url_path);
        if(index == -1) return;
        sprintf(temp, "templates/%s", arr[index]->filename);
        int front_fd = open(temp, O_RDONLY, 0700);
        if(front_fd == -1){
            error("File doesn't exist");
        }
        strcpy(buff, "HTTP/1.0 200 OK\r\n\r\n");
        int c = write(cln_fd, buff, strlen(buff));
        while(c > 0){
            c = read(front_fd, buff, BUFF_SIZE);
            write(cln_fd, buff, c);
        }
        close(front_fd);
    }
}


void read_request(int fd, http_request* request, unsigned short* method)
{
    memset(request->request_data, 0, REQ_SIZE);
    memset(request->path, 0, PATH_SIZE);
    int c = read(fd, request->request_data, REQ_SIZE - 1);


    request->request_data[c] = '\0';
    char* ptr1 = strchr(request->request_data, '/');
    char* ptr2 = strchr(ptr1, ' ');
    *ptr2 = '\0';
    strcpy(request->path, ptr1);
    *ptr2 = ' ';


    fprintf(stdout, "[INFO]Request Path: %s", request->path);
    fprintf(stdout, "\n---------------------------------------\n");
    fprintf(stdout, "[INFO]Request Data:\n");
    fprintf(stdout, "\n");


    if(request->request_data[0] == POST)
    {
        write(STDOUT_FILENO, request->request_data, c);
        while(c >= REQ_SIZE - 1)
        {
            c = read(fd, request->request_data, REQ_SIZE);
            write(STDOUT_FILENO, request->request_data, c);

        }

    }
    else
    {
        write(STDOUT_FILENO, request->request_data, c);
        while(c >= REQ_SIZE - 1)
        {
            c = read(fd, request->request_data, REQ_SIZE);
            write(STDOUT_FILENO, request->request_data, c);

        }
    } 

    fprintf(stdout, "---------------------------------------\n");
    fflush(stdout);
}

void server_init(http_server* serv)
{
    signal(SIGINT, handler);

    unsigned short method;
    http_request request;

    char* buff = (char*)malloc(BUFF_SIZE);
    request.request_data = (char*)malloc(REQ_SIZE);
    request.path = (char*)malloc(PATH_SIZE);

    serv->listening_fd = create_socket(serv->ip_family, serv->trcp_protocol);
    listner_fd = serv->listening_fd;
    bind_to_port(serv->listening_fd, serv->ip_family, serv->port);
    start_listening(serv->listening_fd, serv->q_size);

    fprintf(stdout, "[INFO]Server is listning on port: 127.0.0.1:%d\n", serv->port);
    fflush(stdout);
    while(1)
    {
        int cln_fd = accept_connection(serv->listening_fd);
        
        read_request(cln_fd, &request, &method);
        if(strcmp(request.path, "/favicon.ico") == 0){
            continue;
        }
        create_response(request.path, buff, cln_fd);
        
        close(cln_fd);
        
    }

    exit(EXIT_SUCCESS);
}


