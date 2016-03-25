#include "../socket_includes.h"

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



int main(int argc, char * argv[])
{
	int sockfd, listenfd,maxfd;//sockfd通信套接字， listenfd监听套接字
	struct sockaddr_in server, client;
	char read_buf[256] = {0};
	socklen_t len;
	int i;
	int size;
	int client_fd[FD_SETSIZE];//监听的套接字形成的数组 一般最大有1024个
	
	for(i = 0;i < FD_SETSIZE;i++)
		client_fd[i] = -1;//client_fd数组初始化

	fd_set global_rdfs,current_rdfs;//global关注的套接字集 current当前关注的套接字

	len = sizeof(struct sockaddr_in);

	listenfd = ipv4_tcp_sock_init(server);
	FD_ZERO(&global_rdfs);
	FD_SET(listenfd,&global_rdfs);	
	maxfd = listenfd;

	
	while(1)
	{
		current_rdfs = global_rdfs;//global_rdfs的数值由系统改变
		if(select((maxfd+1),&current_rdfs,NULL,NULL,NULL) < 0)//永久等待
		{
			perror("Select Error.");
			return RT_ERR;
		}
		if(FD_ISSET(listenfd,&current_rdfs))
		{
		sockfd = accept(listenfd,(struct sockaddr *)&client,&len); 		    if(sockfd < 0)
		{
			perror("Accept error");
			return RT_ERR;
		}
		//accept接收到套接字之后
		printf("sockfd:%d\n",sockfd);
		FD_CLR(i,&current_rdfs);//清零
		maxfd = maxfd > sockfd ? maxfd: sockfd;//最大的套接字变成通信套接字
		FD_SET(sockfd,&global_rdfs);//把通信套接字加入观察的file set集里
		for(i = 0;i < maxfd;i++)
		{
			if(-1 == client_fd[i])//套接字不存在 可以存放新的套接字即sockfd
			{
				client_fd[i] = sockfd;
				break;
			}
		}
		}

		
		for(i = 0;i <= maxfd;i++)//i是等待的某个套接字的文件描述符
		{
			if(client_fd[i] == -1)
			continue;//套接字不存在直接检测下一个

			if(FD_ISSET(client_fd[i],&current_rdfs))
		{
				size = recv(client_fd[i],read_buf,sizeof(read_buf),0);
				if(size < 0)
				{
					perror("receive error.");
					return RT_ERR;//退出整个循环 
				}
				if(size == 0)
				{
					printf("Receive finish\n");
					FD_CLR(client_fd[i],&global_rdfs);//从套接字集里去除
					close(client_fd[i]);//关闭
					client_fd[i] = -1;
					continue;//退出本次循环 继续下一次循环
				}
				printf("read_buf:%s",read_buf);
				send(client_fd[i],read_buf,size,0);
					
				}
			}
		}

	}



	

