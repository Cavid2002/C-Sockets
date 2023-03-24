#include"MYNET.h"
#include<pthread.h>
#define BUFF_SIZE 100

int client_fd;


void* show_msg(void* args){
    int fd = *((int*)args);
    char r_buff[BUFF_SIZE];
    int c;
    while(1){
        c = read(fd, r_buff, BUFF_SIZE);
        if(c != 0 || c != -1 || c == 1){
            fprintf(stdout,"From Server:%s\n", r_buff);
            fflush(stdout);
        }
    }
}

void* send_msg(void* args){
    int fd = *((int*)args);
    char w_buff[BUFF_SIZE];
    int c;
    while(1){
        fscanf(stdin, "%s", w_buff);
        write(fd, w_buff, strlen(w_buff));
    }
}

void start_chat(int fd){
    char w_buff[BUFF_SIZE] = "Salam";
    write(fd, w_buff, BUFF_SIZE);
    pthread_t t1;
    if(pthread_create(&t1, NULL, show_msg, &fd) == -1){
        error("Unable to create thread");
    }
    int fd2 = fd;
    send_msg(&fd);
    
}


void handler(int num){
    close(client_fd);
    fprintf(stdout, "\nBYE\n");
    exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]){
    signal(SIGINT, handler);
    client_fd = create_socket(AF_INET, SOCK_STREAM);
    connect_to_port(client_fd, AF_INET, 3340, "127.0.0.1");
    char buff[20];
    start_chat(client_fd);
    close(client_fd);
}