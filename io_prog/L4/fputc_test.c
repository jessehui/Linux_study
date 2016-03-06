//***************************touch function implementation***********
//*******************************************************************
//利用标准io实现
#include "stdio.h"
//#include "unistd.h"
//#include "fcntl.h"

int main(int argc, char *argv[])
{
	//int fd;

	int ret;//return value of fgetc
	FILE *fp; 
	char buff[] = "Hello Linux\n";

	char readbuf[128] = {0};
	fp = fopen("test.txt","w+");//读写方式打开
	
	if(fp == NULL)
	{	printf("open file 'test.txt' failure\n");
		return -1;
	}
	printf("open file 'test.txt' success\n");

	fputc('s',fp);
	rewind(fp);
	
	//start read
	ret = fgetc(fp);//直接读为错误 因为没有重新定义指针位置
	// 需要加fseek或rewind
	printf("ret == %d\n",ret);
	
//	printf("readbuf : %s\n",readbuf);//打印为空 因为位置指针在文件最后
	
	fclose(fp);//关闭文件 
	
	return 0;

}
