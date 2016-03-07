//**************************
#include "stdio.h"
//#include "unistd.h"
//#include "fcntl.h"

int main(int argc, char *argv[])
{
	FILE *fp; 
	char buff[] = "Hello Linux\n";
	char readbuf[128] = {0};
	fp = fopen("test.txt","w+");//读写方式打开
	
	if(fp == NULL)
	{	printf("open file 'test.txt' failure\n");
		return -1;
	}
	printf("open file 'test.txt' success\n");

	//start to write
	fwrite(buff,sizeof(char),sizeof(buff),fp);
	
	rewind(fp);//先写后读 要把文件指针归位
	fread(readbuf,sizeof(char),sizeof(readbuf),fp);//read from test.txt
	printf("readbuf = %s\n",readbuf);
	
	fclose(fp);//关闭文件 
	
	return 0;

}
