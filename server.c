#include"MYNET.h"

void handler(int num){
    close(listner_fd);
    fprintf(stdout, "\nBYE\n");
    exit(EXIT_SUCCESS);
}


int main(int argc, char* argv[]){
    signal(SIGINT, handler);
	listner_fd = create_socket(AF_INET, SOCK_STREAM);
    bind_to_port(listner_fd, AF_INET, 3340);
    
    if(listen(listner_fd, 10) == -1){
        error("Server is busy");
    }

    char buff[20] = "Salam";
    while(1){
        int cl_fd = accept_connection(listner_fd);
        write(cl_fd,buff,20);
        close(cl_fd);
    }
    close(listner_fd);
}