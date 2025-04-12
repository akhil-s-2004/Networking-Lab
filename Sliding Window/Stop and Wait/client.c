#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<ctype.h>

#define MAX 5
#define TIME 3

int main(){
	int new_socket,seq=0,ack;
	struct sockaddr_in server_addr;
	new_socket=socket(AF_INET,SOCK_STREAM,0);
	if(new_socket<0){
		perror("Socket creation failed!!!\n");
		exit(1);
	}
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_addr.sin_port=htons(1212);
	if(connect(new_socket,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
		perror("Connection failed!!!\n");
		exit(1);
	}
	printf("Client connected successfully!!\n");
	while(seq<MAX){
		printf("Sending packet with sequence %d!!\n",seq);
		send(new_socket,&seq,sizeof(seq),0);
		if(recv(new_socket,&ack,sizeof(ack),0)>0)
		{
			if(ack==seq+1){
				printf("Acknowledgement %d recieved!!\n",ack);
				seq=ack;
			}
		}
		else{
			printf("No packet recieved Timeout\nWaiting for acknowledgement %d",seq+1);
		}
	}
	close(new_socket);
