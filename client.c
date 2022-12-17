#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>


#define BUFFER_SIZE 256

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

void define_addr(sockaddr_in* host_adr){
	host_adr->sin_family = AF_INET;
	host_adr->sin_port = htons(8080);
	host_adr->sin_addr.s_addr = INADDR_ANY;
}

int main(int argc,char* argv[]){

	//creating the socket
	int client_socket = socket(AF_INET,SOCK_STREAM,0);

	//define adress
	sockaddr_in client_adr;
	define_addr(&client_adr);

	//connecting
	int connection_status = connect(client_socket,(sockaddr*)&client_adr,sizeof(client_adr));

	if(connection_status < 0){
		printf("[ERROR] CONNECTION ERROR!");
		exit(EXIT_FAILURE);
	}

	//recive data
	char accepted_msg[BUFFER_SIZE];

	recv(client_socket, accepted_msg, sizeof(accepted_msg),0);

	printf("data accepted: %s\n",accepted_msg);

	close(client_socket);

	return 0;

}