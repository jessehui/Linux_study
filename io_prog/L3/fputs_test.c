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
	
	fflush(fp);//强制刷新缓存 所以就能把内容写进文件
	while(1);//把buff中的换行符去掉 则不会打印任何东西 因为fputs是行缓存
	fclose(fp);//关闭文件 
	
	return 0;

}
