#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int fd[2];
	int ret = pipe(fd);
	if(ret < 0)
	{
		printf("create pipe failure\n");
		return -1;
	}

	printf("create pipe sucess fd[0] = %d, fd[1] = %d\n", fd[0],fd[1]);
	//返回3和4. 因为0,1,2都被系统占用了
	return 0;
}

