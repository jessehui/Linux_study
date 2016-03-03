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
	char buff[] = "Hello Linux\n";
	fp = fopen("test.txt","w+");//读写方式打开
	
	if(fp == NULL)
	{	printf("open file 'test.txt' failure\n");
		return -1;
	}
	printf("open file 'test.txt' success\n");

	fputs(buff,fp);

	fclose(fp);//关闭文件 
	
	return 0;

}
