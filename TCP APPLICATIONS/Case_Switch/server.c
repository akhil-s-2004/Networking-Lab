#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<ctype.h>
#include<unistd.h>
#include<sys/socket.h>

#define PORT 6969
#define BUFFER_SIZE 1024

void switch_case(char buffer[]){
	int i;
	char temp;
	for(i=0;i<strlen(buffer)-1;i++)
	{
		if(isupper(buffer[i])){
			temp=tolower(buffer[i]);
			buffer[i]=temp;
		}
		else if(islower(buffer[i])){
			temp=toupper(buffer[i]);
			buffer[i]=temp;
		}
		else{
			continue;
		}
	}
}
int main(){
	int check,server_socket,client_socket;
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
		switch_case(buffer);
		printf("Server: %s",buffer);
		send(client_socket,buffer,strlen(buffer),0);
	}
	close(client_socket);
	close(server_socket);
}
