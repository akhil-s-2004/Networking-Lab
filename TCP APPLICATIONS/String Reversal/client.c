#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 1312
#define BUFFER_SIZE 1024

int main(){
	int client_socket;
	struct sockaddr_in server_addr;
	char buffer[BUFFER_SIZE];

	client_socket=socket(AF_INET,SOCK_STREAM,0);
	if(client_socket==-1){
		perror("Socket creation failed!!\n");
		exit(1);
	}

	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.12");
	server_addr.sin_port=htons(PORT);

	if(connect(client_socket,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
		perror("Connection failed!!\n");
		exit(1);
	}
	printf("Client connected on port %d\n",PORT);
	while(1){
                printf("\nClient: ");
                fgets(buffer,BUFFER_SIZE,stdin);
                send(client_socket,buffer,strlen(buffer),0);

		memset(buffer,0,BUFFER_SIZE);
		if(recv(client_socket,buffer,BUFFER_SIZE,0)<=0){
			printf("Client disconnected!!\n");
			break;
		}
		printf("Server: %s",buffer);
	}
	close(client_socket);
}
