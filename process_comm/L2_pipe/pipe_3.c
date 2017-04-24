#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//写阻塞测试
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

	printf("create pipe success fd[0] = %d, fd[1] = %d\n", fd[0],fd[1]);
	//返回3和4. 因为0,1,2都被系统占用了

	int i;
	for(i = 0; i< 65534; i++)	//会写满 写满会阻塞
	{
		write(fd[1], write_buf, sizeof(write_buf));	

	}
	printf("End writing\n");

	close(fd[0]);
	close(fd[1]);
	return 0;
}

