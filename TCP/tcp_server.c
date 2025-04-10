#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 1212
#define BUFFER_SIZE 1024

int main(){
	int server_socket,client_socket;
	struct sockaddr_in server_addr,client_addr;
	socklen_t addr_size;
	char buffer[BUFFER_SIZE];
	server_socket=socket(AF_INET,SOCK_STREAM,0);
	if(server_socket==-1){
		perror("Socket creation failed!!\n");
		exit(1);
	}
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.12");
	server_addr.sin_port=htons(PORT);
	if(bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		perror("Binding failed!!");
		exit(1);
	}
	if(listen(server_socket,1)<0){
		perror("Listening failed!!!\n");
		exit(1);
	}
	printf("Server is listening on port %d\n",PORT);
	addr_size=sizeof(client_addr);
	client_socket=accept(server_socket,(struct sockaddr*)&client_addr,&addr_size);
	if(client_socket<0)
	{
		perror("ACCEPT FAILED!!\n");
		exit(1);
	}
	while(1){
		memset(buffer,0,BUFFER_SIZE);
		if(recv(client_socket,buffer,BUFFER_SIZE,0)<=0){
			printf("Client disconnected!!\n");
			break;
		}
		printf("Client: %s",buffer);

		printf("Server: ");
		fgets(buffer,BUFFER_SIZE,stdin);
		send(client_socket,buffer,strlen(buffer),0);
	}
	close(client_socket);
	close(server_socket);
}
