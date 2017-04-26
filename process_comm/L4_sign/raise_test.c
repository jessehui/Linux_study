#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main()
{
	printf("before raise\n");	//如果没有\n的话, 这条语句也打印不出来

	raise(9);	//发送9(sigkill)给自己 类似于_exit(), 不是exit(), exit()会把缓存里的打印出来再退出

	printf("After raise\n");

	return 0;
}