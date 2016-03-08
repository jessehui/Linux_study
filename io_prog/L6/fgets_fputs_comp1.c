#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "string.h"

int main(int argc, char *argv[])
{
	FILE *src_fp,*des_fp;
	//int read_ret;
	char read_buf[128] = {0};
	
	if(argc < 3)
	{
		printf("Not enough valid arguments.\n");
		return -1;	
	}
	
	//open source file
	src_fp = fopen(argv[1], "r");//只读方式打开 文件必须存在
	if(src_fp == NULL)
	{
		printf("Open file %s failure.\n",argv[1]);
		return -2;
	}
	
	printf("Open file %s success.\n",argv[1]);

	//open des file
	des_fp = fopen(argv[2],"w");//写方式打开 文件不存在自动创建
	if(des_fp == NULL)
	{
		printf("Open file %s failure.\n",argv[2]);
		return -3;
	}
	
	printf("Open file %s success.\n",argv[2]);
	
	//start write and read
	while(1)
	{
		fgets(read_buf,sizeof(read_buf),src_fp);
		if( feof(src_fp) )
		{
			printf("Read file %s fininshed\n",argv[1]);
			break;
		}
		fputs(read_buf,des_fp);
	}
	
	fclose(src_fp);
	fclose(des_fp);

}
