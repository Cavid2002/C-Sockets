#include"MYNET.h"
#include<fcntl.h>
#include<pthread.h>
#define BUFF_SIZE 1000

void handler(int num){
    close(listner_fd);
    fprintf(stdout, "\nClosing connection\n");
    exit(EXIT_SUCCESS);
}

void create_response(int fd,char response[]){
    char temp[100];
    int c = 1;
    strcpy(response, "HTTP/1.0 200 OK\r\n\r\n");
    FILE* file = fopen("../index.html","r");
    while(fgets(temp,100,file) != NULL){
        strcat(response, temp);
    }
    write(fd, response, strlen(response));
    close(fd);
}

void* get_data(void* arg){
    int fd = *((int*)arg);
    int c = 1;
    char msg[50];
    while(1){
        c = read(fd, msg, 50);
        if(c <= 0){
            continue;
        }
        msg[c] = '\0';
        fprintf(stdout, "%s\n", msg);
    }
    return NULL;
}

int main(int argc, char* argv[]){
    signal(SIGINT, handler);
    listner_fd = create_socket(AF_INET, SOCK_STREAM);
    bind_to_port(listner_fd, AF_INET, 3340);
    start_listening(listner_fd, 10);
    char arr[BUFF_SIZE];
    fprintf(stdout, "SERVER listening on port: 127.0.0.1:3340\n");
    fflush(stdout);
    pthread_t t1;
    while(1){
        memset(arr, 0, BUFF_SIZE);
        int connect_fd = accept_connection(listner_fd);
        pthread_create(&t1, NULL, get_data, &connect_fd);
        create_response(connect_fd,arr);
        
    } 
    pthread_join(t1,NULL);   
    close(listner_fd);
}