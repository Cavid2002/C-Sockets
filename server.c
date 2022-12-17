#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define BUFFER_SIZE 256


typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

void define_addr(sockaddr_in* server_adr){
	server_adr->sin_family = AF_INET;
	server_adr->sin_port = htons(8080);
	server_adr->sin_addr.s_addr = INADDR_ANY;
}
	
int main(int argc,char* argv[]){

	if(argc == 1){
		printf("[ERROR] Message is not specified!\n");
		exit(EXIT_FAILURE);
	}

	char msg[BUFFER_SIZE];
	memcpy(msg,argv[1],strlen(argv[1])+1);

	//creating socket
	int server_socket = socket(AF_INET,SOCK_STREAM,0);

	//define server address
	sockaddr_in server_adr;
	define_addr(&server_adr);


	//binding
	bind(server_socket, (sockaddr*)&server_adr, sizeof(server_adr));

	//listen
	listen(server_socket,5);

	//accepting
	int client_sock = accept(server_socket, NULL, NULL);
	send(client_sock, msg, sizeof(msg),0);


	close(server_socket);

	return 0;


}