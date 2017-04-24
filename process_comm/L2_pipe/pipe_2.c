#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int fd[2];
	int ret = pipe(fd);
	char write_buf[] = "Hello Linux\n";
	char read_buf[128];

	if(ret < 0)
	{
		printf("create pipe failure\n");
		return -1;
	}

	printf("create pipe sucess fd[0] = %d, fd[1] = %d\n", fd[0],fd[1]);
	//返回3和4. 因为0,1,2都被系统占用了

	write(fd[1], write_buf, sizeof(write_buf));	
	//first read
	read(fd[0],read_buf,sizeof(write_buf));

	printf("read_buf = %s\n", read_buf);

	//second read
	read(fd[0],read_buf,sizeof(write_buf));//读完自动删除
	printf("End of block\n");//如果管道里没东西就会被阻塞.

	close(fd[0]);
	close(fd[1]);
	return 0;
}

