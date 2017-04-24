#include "unistd.h"
#include "stdio.h"
#include "sys/types.h"
#include "stdlib.h"

int main()
{
	pid_t pid;
	int receive = 0;
	int fd[2];
	int process_inter = 0;		//用于测试用户空间进程间通信
	
	//建立管道在fork之前 不然会有两条管道
	int ret = pipe(fd);
	if(ret < 0)
	{
		printf("pipe create failure\n");
		return -1;
	}


	pid = fork();	//新建进程
	
	

	if(pid == 0)
	{
		int i = 0;

		while(receive == 0)	//wait
		{
			read(fd[0], &receive, sizeof(int));
		}
		for(i = 0; i < 5; i++)
		{
			printf("this is child process i = %d\n", i);
			usleep(100);	//进程挂起100us
		}
	}

	if(pid > 0)	//parent process
	{
		for(int i = 0; i< 5; i++)
		{
			printf("this is parent process i = %d\n", i);
			usleep(100);
		}

		process_inter = 1;
		write(fd[1], &process_inter, sizeof(int));	//process_inter取地址
	}
	while(1);
	return 0;


}