#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main()
{
	pid_t pid = fork();

while(1)
{
	if(pid > 0)	//父进程
	{
		int i = 0;
		for(;i < 10; i++);
		printf("Parent\n");
	}

	if(pid == 0)	//子进程
	{
		int i = 0;
		for(; i<10;i++);
		printf("Child\n");
	}
}
	return 0;
}

//什么时候轮询到child或者parent是不确定的