#include "stdio.h"
#include "string.h"
#include "unistd.h"

#include "stdlib.h"
#include "time.h"
#include "fcntl.h"

#include "sys/socket.h"
#include "sys/types.h"
#include "netinet/in.h"
#include <arpa/inet.h>


int main(int argc, char *argv[])
{
	int sockfd, recv_ret;
	struct sockaddr_in server, client;//一般都创建 sockaddr_in类型 用的时候转换成sockaddr类
	char buff[128] = {0};
	char read_buf[128] = {0};
	int len,length;
	time_t timep;
	
	sockfd = socket(AF_INET,SOCK_DGRAM,0);//udp用SOCK_DGRAM 参数
	if(sockfd < 0)
	{
		printf("Creating Socket Error\n");
		return -1;
	}

	//configurate the server IP address and port
	bzero(&server,sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(8888);
	server.sin_addr.s_addr = inet_addr("172.16.128.147");

	len = sizeof(struct sockaddr);
	if( bind(sockfd,(struct sockaddr *)&server,len) < 0 )
	{
		printf("Bind Error\n");
		return -2;
	}
	
	length = sizeof(struct sockaddr_in);
	while(1)
	{
	//等待接收
	recv_ret = recvfrom(sockfd, read_buf, sizeof(read_buf),0,
			    (struct sockaddr *)&client,&length);
	if(recv_ret < 0)
	{
		printf("Receive Error\n");
	 	return -3;
	}
	printf("length = %d\n",recv_ret);
	printf("ip:0x%x port: %d\n",ntohl(client.sin_addr.s_addr),ntohs(client.sin_port));
	printf("read_buf: %s\n",read_buf);
	
	
	timep = time(NULL);
	snprintf(buff,sizeof(buff),"%s",ctime(&timep));
	
	sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&client, length);
	
	bzero(&client,length);
	bzero(buff,128);
	bzero(read_buf,128);

	}
	close(sockfd);
	return 1;
}

