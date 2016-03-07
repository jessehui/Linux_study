//***************************touch function implementation***********
//*****************************************************************

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
	
	ret = fgetc(fp);//read another char.
	printf("ret == %d\n",ret);//output -1(EOF) no other char left
	//EOF means error or end

	//test
	clearerr(fp);//clear error and the return value of feof and ferror will be zero	

	printf("feof = %d, ferror = %d",feof(fp),ferror(fp));//return values are 1 and 0
	//Thus, it is the end of file, not error of file

		
	fclose(fp);//关闭文件 
	
	return 0;

}
