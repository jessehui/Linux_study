//*****************实现cp命令的文件拷贝功能***************
//********************************************************

#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "string.h"

int main(int argc, char *argv[])
{
	int rd_fd,wr_fd;//读文件描述符（源文件） 写文件描述符（目标文件）
	char read_buf[128] = {0};
	int rd_ret;

	if(argc < 3)//少于三个参数
	{
		printf("Please input src file and dst file\n");
		return -1;
	}
	
	rd_fd = open(argv[1], O_RDONLY);//read only mode,open source file
	
	if(rd_fd < 0)
	{
		printf("Open src file %s failure.\n", argv[1]);
		return -2;
	}
	
	printf("Open src file %s success. rd_fd = %d\n",argv[1],rd_fd);
	//rd_fd = 3 (0,1,2文件标识符表示特定的文件，从3开始）
	
	wr_fd = open(argv[2], O_WRONLY);// open dest file

	if(wr_fd < 0)
	{
		printf("Open dst file %s failure.\n", argv[2]);
		return -3;
	}
	
	printf("Open dst file %s success. rd_fd = %d",argv[2],wr_fd);
	//wr_fd = 4 (累加）
	
	while(1)
	{	
	rd_ret = read(rd_fd, read_buf, 128);
	//返回实际读的字节数
	
	if(rd_ret < 128)
		break; //读的字节小于128 说明已经读完了 跳出循环
	write(wr_fd, read_buf, rd_ret);
	memset(read_buf,0,128);//缓存清空 需要string.h
	}

	// 最后一次读的还没有写 再写一次
	write(wr_fd,read_buf, rd_ret);
	
	close(rd_fd);
	close(wr_fd);
	return 0;
}
