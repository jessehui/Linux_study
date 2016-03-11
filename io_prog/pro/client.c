//*******************************************************************
//Description: "download (write)" file from server(other directory) 
//              to local(working directory) 
//*******************************************************************
#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "string.h"
#include "dirent.h"
#include "sys/types.h"

int main()
{
	DIR *dp;
	int src_fd,des_fd;
	struct dirent *dir;
	char server[128] = {0};
	char down_file[128] = {0};
	char buff[128] = {0};
	int ret_read;
	
start:	printf("Please type server path and directory name...\n");
	scanf("%s",server);
	
	//#(1)open dir 
	dp = opendir(server);
	if(dp == NULL)
	{
		printf("Server %s open fail.\n",server);
		goto start;
	}
	printf("Server %s open succeed",server);

	//#(2)list the directory
	while(1)
	{
		dir = readdir(dp);
		if(dir != NULL)
		{
			printf("iNode = %ld, dirname = %s\n",dir->d_ino,dir->d_name);
		}
		else
		{
			printf("End of the directory.\n");
			break;
		}
	}

	//#(3)get the name of download file
	printf("Please type in the name of download file...\n");
	scanf("%s",down_file);

	//#(4)download the file
	//open the source file
	src_fd = open(strcat(strcat(server,"/"),down_file),O_RDONLY);
	//format: server/down_file
	
	if(src_fd < 0)
	{
		printf("Open download file %s failure\n",down_file);
		return -2;
	}
	printf("Open download file %s success\n",down_file);
	
	//open des file
	des_fd = open(strcat(down_file,"_cp"),O_CREAT | O_WRONLY,0777);//create new file, write only
	if(des_fd < 0)
	{
		printf("Download file %s failure\n",down_file);
		return -3;
	}
	
	//start to copy source file to des file
	while(1)
	{
		ret_read = read(src_fd,buff,sizeof(buff));
		write(des_fd,buff,ret_read);
		if(ret_read < sizeof(buff))
		{
			printf("Download finish.\n");
			break;
		}

			

	}

	closedir(dp);
	return 0;
}
