#include "socket_includes.h"
#include "stdio.h"
#include "string.h"

int main(int argc, *char argv[])
{
	int sockfd;
	struct sockaddr servaddr;//
	char buff[128] = {0};
	int bytes;
	
	sockfd = socket(AF_INET,//IPV4 internet protocols
			SOCK_STREAM,//通信语义使用STREAM类型
			0);//specified protocols
	if(sockfd < 0)
	{
		perror("socket error");//print a system error message
		return -1;
	}

	bzero(&servaddr, sizeof(servaddr));//wirte zero
	servaddr.sin_family = AF_INET;//使用IPv4协议
	servaddr.sin_ddr.s_addr = inet_addr("127.0.0.1");//指定IP地址
	servaddr.sin_port = htons(8888);//指定端口
	
	if(connect(sockfd,(struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("connect error");
		return -2;
	}
		
	bytes = read(sockfd,buff,sizeof(buf));
	if(bytes < 0)
	{
		printf("read error\n");
		return -3;
	}
	
	printf("Time : %s",buff);
	close(sockfd);

}
