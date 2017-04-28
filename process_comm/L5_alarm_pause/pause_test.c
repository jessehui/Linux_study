#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main()
{
	printf("before pause\n");	//如果没有\n的话, 这条语句也打印不出来

	pause();

	printf("After pause\n");

	while(1);	//在这9秒内 进程不能终止
	return 0;
}