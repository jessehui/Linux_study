//***************************touch function implementation***********
//*******************************************************************
//利用标准io实现
#include "stdio.h"
//#include "unistd.h"
//#include "fcntl.h"

int main(int argc, char *argv[])
{
	//int fd;
	FILE *fp; 
	fp = fopen(argv[1],"w+");//读写方式打开
	
	if(fp == NULL)
	{	printf("create file %s failure\n", argv[1]);
		return -1;
	}
	printf("create file %s success",argv[1]);

	fclose(fp);//关闭文件 
	
	return 0;

}
