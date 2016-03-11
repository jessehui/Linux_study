#include "stdio.h"
#include "dirent.h"
#include "sys/types.h"

int main(int argc, char *argv[])
{
	int ret;
	DIR *dr;
	struct dirent *drt;
	long loc;
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
	printf("open dir success.\n");
	
	//start to read
	while(1)
	{
	loc = telldir(dr);//location before read
	printf("loc = %ld",loc);
	drt = readdir(dr);

	rewinddir(dr);//一直读第一个 等价于seekdir(dr,0);
	if(drt == NULL)
	{
		printf("read dir end\n");
		loc = telldir(dr);
		printf("loc = %ld",loc);
		break;
	}
	printf("read dir success\n");
	printf("inode = %d, dirname = %s\n", drt->d_ino,drt->d_name);

	}
	closedir(dr);
	return 0;
	

}
