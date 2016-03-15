
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


#include <unistd.h>
#include <fcntl.h>



#define MAX_LISTEN_QUE 5





int main(int argc, char *argv[])
{
	int listenfd, sockfd, opt = 1;
	struct sockaddr_in server, client;
	char buf[200];
	socklen_t len;
	int timep;
	int ret;
	
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if(listenfd < 0){
			perror("Create socket fail.");
			return -1;
  }	
	
	if((ret = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) < 0){
  		perror("Error, set socket reuse addr failed");	
  		return -1;
  }
	
	bzero(&server, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port   = htons(8888);
  server.sin_addr.s_addr  = htonl(INADDR_ANY);
	
	len = sizeof(struct sockaddr);
  if(bind(listenfd, (struct sockaddr *)&server, len)<0){
			perror("bind error.");
      return -1;
  }
	
	listen(listenfd, MAX_LISTEN_QUE);
	
	while(1){
		sockfd = accept(listenfd, (struct sockaddr *)&client, &len);
	  if(sockfd < 0){
				perror("accept error.");
				return -1;
	  }
	  
		timep = time(NULL);
		snprintf(buf, sizeof(buf), "%s", ctime(&timep));
		write(sockfd, buf, strlen(buf));
		printf("Bytes:%d\n", strlen(buf));
		printf("sockfd=%d\n", sockfd);
		close(sockfd);
	}
	return 0;
	
}









