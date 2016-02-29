//***************************touch function implementation***********
//*******************************************************************

#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"

int main(int argc, int *argv[])
{
	int fd;
	fd = open("test1.c", O_CREAT | O_EXCL | O_RDWR, 0777);
                //没有创建返回
		
	  	  
	//返回iNODE号
	if(fd < 0)
	{	printf("create  file 'test1.c' failure\n");
		return -1;
	}
	printf("create file 'test1.c' success,fd = %d\n",fd);

	close(fd);//关闭文件 
	
	return 0;

}
