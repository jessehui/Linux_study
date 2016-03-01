#include "stdio.h"
#include "unistd.h"

//通过标准IO调用printf函数
int main()
{
	char buff[] = "Hello Linux\n";//user buffer
	//write(1,buff,sizeof(buff));//标准输出对应文件标识符为1
	printf("%s",buff);
	//while(1); //加入while(1)后，buff的内容不会显示在屏幕上 
	//因为没有从lib buffer转到kernel buffer 除非lib buffer收到\n或者被写满
	return 1;
}
