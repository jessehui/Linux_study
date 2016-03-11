#include "stdio.h"
#include "dirent.h"
#include "sys/types.h"

int main(int argc, char *argv[])
{
	int ret;
	DIR *dr;
	struct dirent *drt;
	if(argc<2)
	{
		printf("Not Valid Command!\n");
		return -1;
	}	
	dr = opendir(argv[1]);
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