#include "stdio.h"
#include "string.h"
#include "unistd.h"

#include "stdlib.h"
#include "time.h"
#include "fcntl.h"

#include "sys/socket.h"
#include "sys/types.h"
#include "netinet/in.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	int sockfd,recv_ret;
	struct sockaddr_in server;
	char buff[128] = "Test Internet";
	char read_buf[128] = {0};
	int length;
	
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd < 0)
	{
		perror("Creating socket error\n");
		return -1;
	}
	
	bzero(&server,sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(8888);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	length = sizeof(struct sockaddr_in);
	sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&server,length);

	recv_ret = recvfrom(sockfd,read_buf,sizeof(read_buf),0,(struct sockaddr*)&server,&length);
	
	if(recv_ret < 0)
	{
		printf("Receive Error\n");
		return -2;
	}	
	printf("read_buf: %s",read_buf);
	close(sockfd);
	return 1;
}
