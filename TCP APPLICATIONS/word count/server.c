#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<ctype.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdlib.h>

#define PORT 6868
#define BUFFER_SIZE 1024
int words,characters;
void num(char buffer[]){
	int i;
	int inword=0;
	words=0,characters=0;
	for(i=0;i<strlen(buffer);i++){
		characters++;
		if(buffer[i]==' '||buffer[i]=='\n'||buffer[i]=='\t'){
			inword=0;
		}
		else if(inword==0){
			inword=1;
			words++;
			characters--;
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
		num(buffer);
		int return_buffer[3]={words,characters};
		printf("Server: No. of characters: %d\n\tNo. of words: %d\n",return_buffer[1],return_buffer[0]);
		send(client_socket,return_buffer,sizeof(return_buffer),0);
	}
	close(client_socket);
	close(server_socket);
}
