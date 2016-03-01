//***************************touch function implementation***********
//*******************************************************************

#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"

int main(int argc, int *argv[])
{
	int fd;
	fd = open("../L1_touch/test2.c", O_TRUNC | O_RDWR);
                //打开文件会把之前的内容删除，读写模式
		//不需要重新创建 所以不需要第三个参数了
	  	  
	//返回iNODE号
	if(fd < 0)
	{	printf("open  file 'test2.c' failure\n");
		return -1;
	}
	printf("open file 'test2.c' success,fd = %d\n",fd);

	close(fd);//关闭文件 
	
	return 0;

}
