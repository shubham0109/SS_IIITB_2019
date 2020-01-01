#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	pid_t pid = fork();
	if (pid == (pid_t)-1)
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}
	else if(pid == (pid_t)0)
	{
		printf("Process id of child: %d\n", getpid());
	}
	else
	{
		printf("Process id of parent: %d\n", getpid());
	}
	exit(EXIT_SUCCESS);
}