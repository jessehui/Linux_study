#include "stdio.h"
#include "dirent.h"
#include "sys/types.h"

int main(int argc, char *argv[])
{
	int ret;
	DIR *dr;
	struct dirent *drt;
	ret = mkdir("./testdir",0777);//权限0777
	
	if(ret == -1)
	{
		printf("make dir failure\n");
		return -1;
	}
	
	printf("make dir success\n");
	
	dr = opendir("../L5");
	if(dr == NULL)
	{
		printf("open dir failure\n");
		return -2;
	}	
	//start to read
	drt = readdir(dr);
	if(drt == NULL)
	{
		printf("read dir failure\n");
		return -3;
	}
	printf("read dir success\n");
	printf("inode = %d, dirname = %s\n", drt->d_ino,drt->d_name);

	printf("open dir success.\n");
	closedir(dr);
	return 0;
	

}
