#include "stdio.h"

int main(int argc, char *argv[])
{
	FILE *fp;
	int t = 10;//test
	
	fp = fopen("fprintf.txt","w+");

	if(fp == NULL)
	{	printf("open file 'fprintf.txt' failure.\n");
		return -1;
	}
	// printf("open file 'fprintf.txt' success\n");
	fprintf(fp,"Open file 'fprintf.txt' success test = %d",t);
	while(1);//测试fprintf是否是行缓存
	//经测试 没有任何输出 说明是行缓存
	return 0;
}
