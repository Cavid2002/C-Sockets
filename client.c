#include"MYNET.h"

int client_fd;

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
    read(client_fd, buff, 20);
    printf("%s",buff);
    close(client_fd);
}