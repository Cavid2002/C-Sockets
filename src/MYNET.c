#include"MYNET.h"

int listner_fd;

void error(const char* msg){
    close(listner_fd);
    fprintf(stderr,"[ERROR]%s!\n",msg);
    exit(EXIT_FAILURE);
}

int create_socket(int domain, int type){
    int fd = socket(domain, type, 0);
    if(fd == -1){
        error("Socket init failure");
    }
    return fd;
}

int start_listening(int fd, int num){
    if(listen(fd, num) == -1){
        error("Unable to listen!");
    }
}

int bind_to_port(int fd, unsigned int family, unsigned short port){
    sockaddr_in name;
    name.sin_family = family;
    name.sin_port = htons(port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    char reuse = 1;
    if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1){
        error("Couldn't reuse port");
    }

    if(bind(fd, (sockaddr*)&name, sizeof(name)) == -1){
        error("Couldn't bind to port");
    }
}

int accept_connection(int fd, sockaddr_in* client_addr){
    unsigned int addr_size = sizeof(sockaddr_in);
    int cd = accept(fd, (sockaddr*)client_addr, &addr_size);
    if(cd == -1){
        error("Unable to connect");
    }
    return cd;
}

int connect_to_port(int fd, int ip_family, unsigned short port, const char* ip_addr){
    sockaddr_in name;
    memset(&name, 0, sizeof(name));
    name.sin_family = ip_family;
    name.sin_addr.s_addr = inet_addr(ip_addr);
    name.sin_port = htons(port);
    int c = connect(fd, (sockaddr*)&name, sizeof(name));
    if(c == -1){
        error("Couldn't connect!");
    }
    return c;
}