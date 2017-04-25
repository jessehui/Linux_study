#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>


int main()
{
	char process_inter = 0;//通信信号

	//打开管道文件
	int fd = open("./myfifo", O_WRONLY);//第一个进程往管道里写

	if(fd < 0)
	{
		printf("Open fifo failure\n");
		return -1;
	}

	printf("open fifo success\n");


	for(int i=0; i<5; i++)
	{
		printf("This is first process i = %d\n", i);
		usleep(100);
	}

	process_inter = 1;

	sleep(5);	//睡眠5s
	write(fd, &process_inter, sizeof(char));

	printf("All done \n");
	while(1);
	return 0;
}