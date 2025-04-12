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
	int server_socket,new_socket,seq,ack=0;
	struct sockaddr_in server_addr;
	struct sockaddr_storage server_storage;
	struct timeval timeout={TIME,0};
	socklen_t addr_size;
	server_socket=socket(AF_INET,SOCK_STREAM,0);
	if(server_socket<0){
		perror("Socket creation failed!!!\n");
		exit(1);
	}
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_addr.sin_port=htons(1212);
	if(bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
		perror("Bind failed!!!\n");
		exit(1);
	}
	if(listen(server_socket,5)<0)
	{
		perror("Listen failed!!\n");
		exit(1);
	}
	printf("Server is listening!!\n");
	addr_size=sizeof(server_storage);
	new_socket=accept(server_socket,(struct sockaddr*)&server_storage,&addr_size);
	if(new_socket<0){
		perror("Accept failed!!\n");
		exit(1);
	}
	setsockopt(new_socket,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout));
	while(ack<MAX){
		if(recv(new_socket,&seq,sizeof(seq),0)>0)
		{
			if(ack==seq){
				printf("Packet with sequence %d recieved successfully!!\n",seq);
				ack++;
				printf("Acknowledgement %d sent!!\n",ack);
				send(new_socket,&ack,sizeof(ack),0);
			}
			else{
				printf("Duplicate or false packet recieved!!!\nWaiting for packet %d\n",ack);
			}
		}
		else{
			printf("No packet recieved Timeout\nWaiting for sequence %d",ack);
		}
	}
	close(server_socket);
	close(new_socket);
}
