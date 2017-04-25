#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main()
{
	char receive;
	//打开管道
	int fd = open("./myfifo", O_RDONLY);
	
	if(fd < 0)
	{
		printf("Open fifo failure\n");
		return -1;
	}

	printf("open fifo success\n");

	read(fd, &receive, sizeof(char));	//读不到东西就会阻塞

	if(receive == 1)
	{
		printf("receive success\n");
	}
	else
		printf("receive failure\n");

	int i;
	for(i=0; i<5; i++)
	{
		printf("This is second process i = %d\n", i);
		usleep(100);
	}

	while(1);
	return 0;
}