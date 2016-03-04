#include "stdio.h"
int main()
{
	//printf("hello linux");//不会显示到屏幕上
	
	fputs("hellow linux\n", stdout);//或者不加\n 而加上fflush函数
	//或者
	//fputs("hellow linux",stdout);
	//fflush(stdout);
	
	while(1);
	return 0;
}
