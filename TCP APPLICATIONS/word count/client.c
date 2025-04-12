#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 6868
#define BUFFER_SIZE 1024

int main(){
	int client_socket;
	struct sockaddr_in server_addr;
	char buffer[BUFFER_SIZE];
	char full_message[BUFFER_SIZE*5];
	int output[3];

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
 	        printf("Client (type END to finish input):\n");

        // clear the full_message buffer
        	memset(full_message, 0, sizeof(full_message));

        	while(strcmp(buffer, "END\n") != 0){
            		fgets(buffer, BUFFER_SIZE, stdin);
            		strcat(full_message, buffer);  // accumulate lines
			if(strcmp(buffer, "END\n") == 0)
			{
				break;
			}
		}
        	send(client_socket, full_message, strlen(full_message), 0);

	        if(recv(client_socket, output, sizeof(output), 0) <= 0){
          		printf("Client disconnected!!\n");
            		break;
		}
        	printf("Server: No. of characters: %d\n\tNo. of words: %d\n\tNo. of lines: %d\n", output[2], output[0], output[1]);
    	}

    	close(client_socket);
}
