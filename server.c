#include"MYNET.h"
#include<pthread.h>
#define BUFF_SIZE 100



void handler(int num){
    close(listner_fd);
    fprintf(stdout, "\nBYE\n");
    exit(EXIT_SUCCESS);
}


void* show_msg(void* args){
    int fd = *((int*)args);
    char r_buff[BUFF_SIZE];
    int c;
    while(1){
        c = read(fd, r_buff, BUFF_SIZE);
        if(c != 0 || c != -1 || c == 1){
            fprintf(stdout,"From User:%s\n", r_buff);
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
    char r_buff[BUFF_SIZE];
    write(fd, w_buff, BUFF_SIZE);
    pthread_t t1;
    pthread_create(&t1, NULL, show_msg, &fd);
    int fd2 = fd;
    send_msg(&fd);
    
}

int main(int argc, char* argv[]){
    signal(SIGINT, handler);
	listner_fd = create_socket(AF_INET, SOCK_STREAM);
    bind_to_port(listner_fd, AF_INET, 3340);
    
    if(listen(listner_fd, 10) == -1){
        error("Server is busy");
    }    
    
    while(1){
        int cl_fd = accept_connection(listner_fd);
        pid_t id = fork();
        if(id == 0){
            start_chat(cl_fd);     
            close(cl_fd);
            exit(0);
        }
        
    }
    close(listner_fd);
}