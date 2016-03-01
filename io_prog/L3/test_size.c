//test size of printf buffer
//因为只有当lib buffer写满时 才会调用kernel buffer 即调用系统函数
//所以测试一下 printf buffer大小

#include "stdio.h"
#include "unistd.h"

//通过标准IO调用printf函数
int main()
{
	char buff[] = "Hello Linux";//user buffer
	int i = 1;
	while(i <= 93)
	{
		printf("%s",buff);
		i++;
	}//总共写了90*11 = 990 没显示
	//95*11 显示了
	//93*11 没显示 加入显示lm 显示到l 说明一共有 93*11+1 = 1024
	//缓存写满了 就会调用系统函数
	
	printf("lm");
	while(1);//写满了就显示结果 没写满不显示
	return 1;
}
