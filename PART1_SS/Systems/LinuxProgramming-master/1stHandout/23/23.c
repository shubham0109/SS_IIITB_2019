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
		// until parent will not terminate child process will
		// be in zoombie state
		printf("Child terminating.\n");
	}
	else
	{
		printf("pid of parent: %d\n", getpid());
		printf("Press some key to terminate parent.\n");
		getchar();
	}
	exit(EXIT_SUCCESS);
}