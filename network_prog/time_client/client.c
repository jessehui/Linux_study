#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "unistd.h"
#include "fcntl.h"

#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"


int main(int argc, char * argv[])
{
	int sockfd;
	struct sockaddr_in servaddr;//
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

	//get message from the host and the port which are defined here
	bzero(&servaddr, sizeof(servaddr));//wirte zero
	servaddr.sin_family = AF_INET;//使用IPv4协议
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");//指定IP地址
	servaddr.sin_port = htons(8888);//指定端口
	
	if(connect(sockfd,(struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("connect error");
		return -2;
	}
		
	bytes = read(sockfd,buff,sizeof(buff));
	if(bytes < 0)
	{
		printf("read error\n");
		return -3;
	}
	printf("Read Bytes:%d\n",bytes);
	printf("Time : %s\n",buff);
	close(sockfd);

}
