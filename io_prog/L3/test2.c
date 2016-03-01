//***************************touch function implementation***********
//*******************************************************************

#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"

int main(int argc, int *argv[])
{
	int fd;
	char buf[] = "Hello Linux\n";
	
	char read_buf[64] = {0};

	int wr_ret;//return value of write function
	int rd_ret;//return value of read function
	fd = open("test2.c", O_TRUNC | O_RDWR);
                //打开文件会把之前的内容删除，读写模式
		//不需要重新创建 所以不需要第三个参数了
	  	  
	//返回iNODE号
	if(fd < 0)
	{	printf("open  file 'test2.c' failure\n");
		return -1;
	}
	printf("open file 'test2.c' success,fd = %d\n",fd);
	
	// start write
	wr_ret = write(fd, //file name
	      	       buf, //content that will be written
		       sizeof(buf));
	printf("wr_ret = %d\n", wr_ret);

	//start read
	
	//lseek(fd,0,SEEK_SET);//adjust the pointer to the beginning 
	//test
	lseek(fd,-3,SEEK_CUR);
	rd_ret = read(fd, read_buf, sizeof(read_buf));
	printf("rd_ret = %d\nread buffer = %s\n", rd_ret,read_buf);
	
	close(fd);//关闭文件 
	
	return 0;

}
