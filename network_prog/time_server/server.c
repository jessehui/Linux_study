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

int main(int argc, char * argv[])
{
	int sockfd, listenfd;//sockfd通信套接字， listenfd监听套接字
	struct sockaddr_in server, client;
	int ret_bind;
	char buff[256] = {0};
	socklen_t len;
	time_t timep;//#define time_t int
	
	listenfd = socket(AF_INET,SOCK_STREAM,0);
	if(listenfd < 0)
	{
		printf("Create socket fail\n");
		return -1;
	}

	bzero(&server,sizeof(server));//地址后的size个bytes全为0
	server.sin_family = AF_INET;//IPV4协议族
	server.sin_port = htons(8888);//hostshort from host tyte order to network byte order
	server.sin_addr.s_addr = htonl(INADDR_ANY);//绑定服务器上所有网络接口

	len = sizeof(struct sockaddr);	
	//绑定套接字
	ret_bind = bind(listenfd,(struct sockaddr *)&server,len);
	//(struct sockaddr *)&serve 强制转换成sockaddr的指针
	
	if(ret_bind < 0)
	{
		printf("Bind Error\n");
		return -2;
	}
	
	listen(listenfd,MAX_LISTEN_QUE);
	
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

