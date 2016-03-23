#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

#include "sys/socket.h"
#include "sys/types.h"
#include "netinet/in.h"

#include "unistd.h"
#include "fcntl.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



//最大监听队列
#define MAX_LISTEN_QUE 5
//server port 
#define SERV_PORT 8888

int ipv4_tcp_sock_init(struct sockaddr_in server)
{
	int sockfd;//监听套接字
	int len;
	int ret_bind;//return value of bind function

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0)
	{
		perror("Create socket error");
		return -1;
	}

	bzero(&server,sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(SERV_PORT);
	//server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	len = sizeof(struct sockaddr);
	ret_bind = bind(sockfd,(struct sockaddr *)&server,len);
	if(ret_bind < 0)
	{
		perror("Bind Error");
		return -2;
	}	
	
	listen(sockfd,MAX_LISTEN_QUE);
	return sockfd;
	
}

int process_data(int sockfd)
{
	time_t timep;
	char buff[128] = {0};
	char read_buf[128] = {0};
	int size;
	
	while(1)
	{	
		size = recv(sockfd,read_buf,sizeof(read_buf),0);//receive from connection of client which has been built already
		if(size < 0)
		{
			perror("Receive failed.");
			return -1;
		}
		
		if(size == 0)
		{
			perror("Connection Closed.");
			return -2;	
		}
		
		printf("Comments of Client: %s\n",read_buf);//test
		if(strcmp(read_buf,"q") == 0)
		{
			printf("End\n");
			return 1;
		}	
	
		strcpy( buff,strcat(read_buf,"_test_") );
		
		send(sockfd,buff,size,0);//flag是0
	
	}
	close(sockfd);
	return 0;
}


int main(int argc, char * argv[])
{
	int sockfd, listenfd;//sockfd通信套接字， listenfd监听套接字
	struct sockaddr_in server, client;
	char buff[256] = {0};
	socklen_t len;
	time_t timep;//#define time_t int
	
	listenfd = ipv4_tcp_sock_init(server);	

	
	while(1)
	{
	sockfd = accept(listenfd,(struct sockaddr *)&client,&len);
	//sockfd = accept(listenfd,(struct sockaddr *)NULL,NULL);
	if(sockfd < 0)
	{
		printf("Accept Error\n");
		return -3;
	}
	if( fork() == 0 )
	{
		close(listenfd);//关闭监听套接字
		process_data(sockfd);//处理函数
		exit(0);
	}
	
	close(sockfd);//父进程关闭已连接的套接字

	}
	return 0;
}	

