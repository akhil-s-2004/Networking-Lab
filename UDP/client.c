#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 1717
#define BUFFER_SIZE 1024

int main(){
	int client_socket;
	struct sockaddr_in server_addr;
	socklen_t addr_size=sizeof(server_addr);
	char buffer[BUFFER_SIZE];

	client_socket=socket(AF_INET,SOCK_DGRAM,0);
	if(client_socket==-1){
		perror("Socket creation failed!!\n");
		exit(1);
	}
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.4");
	server_addr.sin_port=htons(PORT);
	printf("UDP CLIENT IS READY!!!\n");

	while(1){
		printf("CLIENT: ");
		fgets(buffer,BUFFER_SIZE,stdin);
		sendto(client_socket,buffer,strlen(buffer),0,(struct sockaddr*)&server_addr,addr_size);
		memset(buffer,0,BUFFER_SIZE);
		recvfrom(client_socket,buffer,BUFFER_SIZE,0,(struct sockaddr*)&server_addr,&addr_size);
		printf("SERVER: %s",buffer);
	}
	close(client_socket);
}
