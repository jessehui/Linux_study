#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int ret;
	ret = mkfifo("./myfifo",0777);

	if(ret < 0)
	{
		printf("make fifo failure\n");
		return -1;
	}

	printf("Success\n");
	return 0;
}