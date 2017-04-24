#include "unistd.h"
#include "stdio.h"
#include "sys/types.h"
#include "stdlib.h"

int main()
{
	pid_t pid;
	int process_inter = 0;		//用于测试用户空间进程间通信
	pid = fork();	//新建进程

	if(pid == 0)
	{
		int i = 0;
	//	while(process_inter == 0);	//wait
		for(int i = 0; i < 5; i++)
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
	}
	while(1);
	return 0;


}