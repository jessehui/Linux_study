#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"


int thread_inter = 0;

void* fun(void *var)	//child thread
{
	int j;
	while(thread_inter == 0);	//
	for(j = 0; j < 10; j++)
	{
		usleep(100);
		printf("this is fun j = %d \n", j);
	}

}


int main()	//main thread
{
	int i;
	char str[] = "hello Linux\n";

	pthread_t tid;
	int ret;
	ret = pthread_create(&tid, NULL, fun, (void*)str);

	if(ret < 0)
	{
		printf("create thread failure\n");
		return -1;
	}

	for(i = 0; i < 10; i++)
	{
		usleep(100);
		printf("this is main i = %d\n",i);
		if(i == 3)
			thread_inter = 1;

		if(i == 8)
			thread_inter = 0;
	}

	thread_inter = 1;
	while(1);
	return 0;
}



//利用用户空间信号量来达到线程间通信
//不能用于进程间通信


