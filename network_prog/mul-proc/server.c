#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

#include "sys/socket.h"
#include "sys/types.h"
#include "netinet/in.h"

#include "unistd.h"
#include "fcntl.h"

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
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	
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
	
	//延时
	//sleep(10);
	//读时间
	time(&timep);
	
	//sprintf(buff,"%s",ctime(&timep));
	snprintf(buff,sizeof(buff),"%s",ctime(&timep));
	printf("buff = %s",buff);
	write(sockfd,buff,strlen(buff));
	printf("Bytes Server = %ld\n",sizeof(buff));
	sleep(10);//延时	
	close(sockfd);
	}
	return 0;
}	

