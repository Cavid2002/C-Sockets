#include"MYNET.h"
#include<fcntl.h>
#define BUFF_SIZE 400

void handler(int num){
    close(listner_fd);
    fprintf(stdout, "\nBYE\n");
    exit(EXIT_SUCCESS);
}



int main(int argc, char* argv[]){
    signal(SIGINT, handler);
    listner_fd = create_socket(AF_INET, SOCK_STREAM);
    bind_to_port(listner_fd, AF_INET, 3340);
    start_listening(listner_fd, 10);
    char arr[BUFF_SIZE];
    fprintf(stdout, "SERVER listening on port: 3340\n");
    while(1){
        memset(arr, 0, BUFF_SIZE);
        int connect_fd = accept_connection(listner_fd);
        int fd = open("index.html", O_RDONLY, 777);
        int c;
        while(c <= 0){
            c = read(fd, arr, BUFF_SIZE - 1);
            write(listner_fd, arr, c);
        }
        close(fd);
    }    
    close(listner_fd);
}