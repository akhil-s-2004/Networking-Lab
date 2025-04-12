#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 1717
#define BUFFER_SIZE 1024

int main(){
	int  server_socket;
	struct sockaddr_in server_addr,client_addr;
	socklen_t addr_size=sizeof(client_addr);
	char buffer[BUFFER_SIZE];

	server_socket=socket(AF_INET,SOCK_DGRAM,0);
	if(server_socket==-1){
		perror("Socket creation failed!!!\n");
		exit(1);
	}
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.4");
	server_addr.sin_port=htons(PORT);

	if(bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
		perror("Bind failed!!!\n");
		exit(1);
	}
	printf("Server listening at port %d..",PORT);
	while(1){
		memset(buffer,0,BUFFER_SIZE);
		recvfrom(server_socket,buffer,BUFFER_SIZE,0,(struct sockaddr*)&client_addr,&addr_size);
		printf("CLIENT: %s",buffer);

		printf("SERVER: ");
		fgets(buffer,BUFFER_SIZE,stdin);
		sendto(server_socket,buffer,strlen(buffer),0,(struct sockaddr*)&client_addr,addr_size);
	}
	close(server_socket);
}
