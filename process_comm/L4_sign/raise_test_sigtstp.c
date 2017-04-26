#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main()
{
	pid_t pid = fork();

	if(pid > 0)	//父进程
	{
		sleep(8);	//睡眠状态
		printf("Parent end\n");
		while(1);	//运行状态
	}

	if(pid == 0)	//子进程
	{
		printf("before raise\n");	

		raise(SIGTSTP);	//暂停状态

		printf("After raise\n");

	}
	return 0;
}