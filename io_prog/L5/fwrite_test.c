//**************************
#include "stdio.h"
//#include "unistd.h"
//#include "fcntl.h"

int main(int argc, char *argv[])
{
	FILE *fp; 
	char buff[] = "Hello Linux\n";

	char buf[128] = {0};
	fp = fopen("test.txt","w+");//读写方式打开
	
	if(fp == NULL)
	{	printf("open file 'test.txt' failure\n");
		return -1;
	}
	printf("open file 'test.txt' success\n");

	//start to write
	fwrite(buff,sizeof(char),sizeof(buf),fp);
	while(1);//test 看是否是行缓存 没有显示 则不是行缓存 是全缓存
	
	fclose(fp);//关闭文件 
	
	return 0;

}
