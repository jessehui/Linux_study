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

#include <sys/types.h>
#include <sys/wait.h>


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
	char read_buf[128];
	char * s;
	int size = 0,ret_cmp,ret_cmp2;
	
	while(1)
	{	
		memset(read_buf,0,size);//initialize
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
		printf("%x	%x	%x\n",read_buf[0],read_buf[1],read_buf[2]);
		send(sockfd,read_buf,size,0);//flag是0
		
		*s = read_buf[0];
		ret_cmp = strcmp(s,"q");
		printf("ret_cmp:%d\n",ret_cmp);
		if(ret_cmp == 0)//
		{
			printf("End\n");
			return 1;
		}	
		
		ret_cmp2 = strcmp(s,"c");
		printf("ret_cmp2:%d\n",ret_cmp);
		if(ret_cmp2 == 0)
		{
			printf("Test C\n");
			memset(read_buf,0,sizeof(read_buf));
			sprintf(read_buf,"%s","Test C\n");
			send(sockfd,read_buf,sizeof(read_buf),0);
			
		}
			
			
	}
	close(sockfd);
	return 0;
}

int process_signal(int sigo)
{
	switch(sigo)
	{
		case SIGCHLD://子进程退出时向父进程发送该信号
		printf("Wait...\n");
		while(waitpid(-1,NULL,WNOHANG) > 0);
		printf("Process released.\n");
		break;
		
	}
}

int set_signal_handler(void)
{
	struct sigaction act,oact;
	act.sa_handler = (void *)process_signal;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_flags |= SA_RESTART;
	if(sigaction(SIGCHLD,&act,&oact) < 0)
	{
		return -1;
	}
	return 0;
}

int main(int argc, char * argv[])
{
	int sockfd, listenfd;//sockfd通信套接字， listenfd监听套接字
	struct sockaddr_in server, client;
	char buff[256] = {0};
	socklen_t len;
	time_t timep;//#define time_t int
	
	set_signal_handler();
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

