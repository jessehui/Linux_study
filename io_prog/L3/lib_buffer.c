#include "stdio.h"
#include "unistd.h"

//通过文件IO直接调用系统的write函数写到文件里
int main()
{
	char buff[] = "Hello Linux\n";
	write(1,buff,sizeof(buff));//标准输出对应文件标识符为1
	return 1;
}
