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

	char readbuf[128] = {0};
	fp = fopen("test.txt","w+");//读写方式打开

	if(fp == NULL)
	{	printf("open file 'test.txt' failure\n");
		return -1;
	}
	printf("open file 'test.txt' success\n");

	fputs(buff,fp);
	
	//重新定位指针位置
	fseek(fp,0,SEEK_SET);
	
	fgets(readbuf,128,fp);
	printf("readbuf : %s\n",readbuf);//打印为空 因为位置指针在文件最后

	fclose(fp);//关闭文件 
	
	return 0;

}
