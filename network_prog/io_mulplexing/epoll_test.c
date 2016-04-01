#include "../socket_includes.h"
#include <sys/epoll.h>//epoll头文件
#include "fcntl.h" //fcntl 头文件
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

int cus_process_data(int socketfd)//process data function
{
	int bytes;//size of data received
	char read_buf[128];
	if(socketfd <= 0)//null socket
	{
		printf("Null Socket.\n");
		return -1;
	}
	bytes = recv(socketfd,read_buf,sizeof(read_buf),0);//receive data
	if(bytes < 0)
	{	
		printf("bytes = %d\n",bytes);
		perror("receive error");
		return -1;
	}
	if(bytes == 0)
	{
		printf("receive finish\n");
		return -2;
	}

	//after read
	printf("read_buf:%s\n",read_buf);
	send(socketfd,read_buf,bytes,0);
	return 0;
}

int main(int argc, char * argv[])
{
	int epollfd,listenfd,fd_active;
	int socketfd;//communication socket
	int ret_epol_ctl;//return value of epoll_ctl
	int ret_pro_data;//return value of process data function
	struct epoll_event ev;	
	struct epoll_event events[MAX_EVENTS];//can store all events that epoll wait for
	int i;
	struct sockaddr_in client,server;
	int len = sizeof(struct sockaddr_in);
	
	listenfd = ipv4_tcp_sock_init(server);
	epollfd = epoll_create(MAX_EVENTS);//使用的是非阻塞式套接字
	if(epollfd < 0)
		{
			perror("epoll create failed");
			return -1;
		}

	fcntl(listenfd, F_SETFL,O_NONBLOCK);//设置监听套接字为非阻塞状态
	
	ev.data.fd = listenfd;
	ev.events = EPOLLIN;//关注数据可读的状态（IN 输入）
	ret_epol_ctl = epoll_ctl(epollfd,EPOLL_CTL_ADD,listenfd,&ev);//把listenfd加入关注的事件
	if(ret_epol_ctl < 0)
	{
		perror("epoll control error");
		return -1;
	}

	while(1)
	{
		fd_active = epoll_wait(epollfd,events,MAX_EVENTS,-1);//等待关注事件的套接字集
		//-1 means wait forever
		if(fd_active < 0)
		{
			perror("epoll wait error");
			return -1;
		}
		
		for(i = 0;i<=fd_active;i++)
		{
			if(events[i].data.fd == listenfd)//if true, means new client is comming
			{
				socketfd = accept(listenfd,(struct sockaddr *)&client, &len);
				if(socketfd < 0)
					{
						perror("accept error");
						continue;//one error don't affect others
					}
				
				ev.data.fd = socketfd;
				ev.events = EPOLLIN | EPOLLET;//EPOLLET means to set the 
				//edge triggered behavior for the file descriptor.

				//add new communication socket to the watching list	
				epoll_ctl(epollfd,EPOLL_CTL_ADD,socketfd,&ev);
				continue;
			}
			else//if not the new client, but the data come in
			{
				//custome-defined data process function
				printf("events[%d].data.fd = %d\n",i,events[i].data.fd);
				ret_pro_data = cus_process_data(events[i].data.fd);
				if(ret_pro_data == -2)//receive finish, client end connection by its own
				{
					//clean the socket that I was watching 
					epoll_ctl(epollfd,EPOLL_CTL_DEL,events[i].data.fd,&ev);
					close(events[i].data.fd);
					continue;
				}
			}
		}
	}
	
}













