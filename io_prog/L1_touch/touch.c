//***************************touch function implementation***********
//*******************************************************************

#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"

int main(int argc, int *argv[])
{
	int fd;
	fd = open(argv[1],//文件名，路径
		  O_CREAT | O_RDWR, // 表示新建一个文件 同时可以以读写方式打开
	  	  0777); // 新建文件的权限 0777 所有可读可执行可写 must be 0777 not 777!
	//返回iNODE号
	if(fd < 0)
	{	printf("create file %s failure\n", argv[1]);
		return -1;
	}
	printf("create file %s success,fd = %d\n",argv[1],fd);

	close(fd);//关闭文件 
	
	return 0;

}
