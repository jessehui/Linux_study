#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "string.h"

int main(int argc, char *argv[])
{
	FILE *src_fp,*des_fp;
	int read_ret;
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

	//1. wrong ! 这种方法不能全部读完 因为可能单元数不是缓存的整数倍
/*	while(1)
	{
		fread(read_buf,sizeof(char), sizeof(read_buf),src_fp);
		if( feof(src_fp) )
		{
			printf("Read file %s fininshed\n",argv[1]);
			break;
		}
		
		fwrite(read_buf,sizeof(char),sizeof(read_buf),des_fp);
	}
*/
	
	//2. right !
	while(1)
	{
		read_ret = fread(read_buf,sizeof(char),sizeof(read_buf),src_fp);
		if(read_ret < 128)//读的字节数小于128 说明已经到结尾
		{
			printf("Read file %s finished.\n",argv[1]);
			break;
		}
		
		fwrite(read_buf,sizeof(char),sizeof(read_buf),des_fp);
	}
	
	//最后一次的还没写
	fwrite(read_buf,sizeof(char),read_ret,des_fp);
		
	fclose(src_fp);
	fclose(des_fp);
	return 1;

}
