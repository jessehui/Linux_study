#include "stdio.h"
#include "string.h"
#include "fcntl.h"
#include "unistd.h"

int main(int argc, char *argv[])
{
	FILE *src_fp;
	int read_ret;
	if(argc < 2)
	{
		printf("Not valid command\n");
		return -1;
	}
	
	src_fp = fopen(argv[1], "r");//只读方式打开 文件必须存在
	if(src_fp == NULL)
	{
		printf("Open sorce file %s failure.\n",argv[1]);
		return -2;
	}
	printf("Open source file %s success.\n",argv[1]);
	
	//start read
	while(1)
	{
		read_ret = fgetc(src_fp);
		if(feof(src_fp))//end of the file, no need to write
		{	
			printf("\nEnd of the File\n");
			break;
		}
		fputc(read_ret,stdout);//stdout open automatically
	}

	fclose(src_fp);
	
	return 1;
}
