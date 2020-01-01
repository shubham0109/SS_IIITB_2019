#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	int pid;
	if((pid = fork()) == -1)
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}
	else if(pid == 0)
	{
		printf("parent pid of child: %d\n", getppid());
		sleep(5);
		// parent will terminate before child so child will become
		// orphan and get assigned to the systemd process with pid 1
		printf("parent pid of child after sleep: %d\n", getppid());
	}
	else
	{
		printf("pid of parent: %d\n", getpid());
	}
	exit(EXIT_SUCCESS);
}