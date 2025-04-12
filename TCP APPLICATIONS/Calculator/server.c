//INPUT FORMAT:  A+B OR A-B OR A/B OR A*B @Client.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 1212
#define BUFFER_SIZE 1024

int calc(char buffer[])
{
	int i,j=0,k;
	int result=0;
	char num1[100];
	char num2[100];
	char sym[5];
	int len=strlen(buffer);
	for(i=0;i<len;i++)
	{
		if(buffer[i]=='+')
		{
			strcpy(sym,"+");
			break;
		}
                else if(buffer[i]=='-')
                {
                        strcpy(sym,"-");
                        break;
                }
                else if(buffer[i]=='/')
                {
                        strcpy(sym,"/");
                        break;
                }
                else if(buffer[i]=='*')
                {
                        strcpy(sym,"*");
                        break;
                }

	}
	do{
		num1[j]=buffer[j];
		j++;
	}
	while(buffer[j]!=sym[0]);
	int n1=atoi(num1);
	i=0;
	for(k=j+1;k<len;k++)
	{
		num2[i]=buffer[k];
		i++;
	}
	int n2=atoi(num2);
	if(sym[0]=='+')
	{
		result=n1+n2;
	}
        else if(sym[0]=='-')
        {
                result=n1-n2;
        }
        else if(sym[0]=='/')
        {
                if(n2==0){
			printf("Divide by zero not possible!!\n");
			result=-1;
		}
		else{
			result=n1/n2;
		}
        }
        else if(sym[0]=='*')
        {
                result=n1*n2;
        }
	return result;

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
		printf("\nClient: %s",buffer);
		int result=calc(buffer);
		sprintf(buffer,"%d",result);
		send(client_socket,buffer,strlen(buffer),0);
		printf("Server: Result: %d",result);
	}
	close(client_socket);
	close(server_socket);
}
