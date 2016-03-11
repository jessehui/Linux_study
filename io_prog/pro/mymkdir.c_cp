#include "stdio.h"
#include "dirent.h"
#include "sys/types.h"

int main(int argc, char *argv[])
{
	int ret;
	DIR *dr;
	ret = mkdir("./testdir",0777);//权限0777
	
	if(ret == -1)
	{
		printf("make dir failure\n");
		return -1;
	}
	
	printf("make dir success\n");
	
	dr = opendir("./testdir");
	if(dr == NULL)
	{
		printf("open dir failure\n");
		return -2;
	}	
	printf("open dir success.\n");
	closedir(dr);
	return 0;
	

}
