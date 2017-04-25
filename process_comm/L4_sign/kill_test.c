#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		printf("Not enough parameters\n");
		return -1;
	}

	int sig = atoi(argv[1]);
	int pid = atoi(argv[2]);

	printf("sig = %d, pid = %d \n", sig, pid);

	kill(pid, sig);

	printf("Done\n");

	return 0;




}


