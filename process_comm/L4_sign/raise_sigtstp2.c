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
		printf("Parent end sleep\n");

							//设置为非阻塞
		if(waitpid(0, NULL, WNOHANG) == 0)	//等待子进程结束
		{
			kill(pid-1, 9);	//此时pid为子进程pid, pid-1为父进程
		}

		//不加wait()函数 就会出现僵尸进程 因为没有回收
		wait(NULL);
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