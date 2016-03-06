#include "stdio.h"

int main(int argc, char *argv[])
{
	int t = 10;//test
	char buff[32] = {0};

	sprintf(buff,"t = %d", t);
	
	//test if the buff is assigned
	printf("buff = %s",buff);
	
	return 0;

}
