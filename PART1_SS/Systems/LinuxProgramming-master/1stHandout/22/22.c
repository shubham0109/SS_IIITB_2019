#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(fd == -1)
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}
	pid_t pid = fork();
	if (pid == (pid_t)-1)
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}
	else if(pid == (pid_t)0)
	{
		if(write(fd, "Written by child.\n", 18) == -1)
		{
			perror("write()");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if(write(fd, "Written by parent.\n", 19) == -1)
		{
			perror("write()");
			exit(EXIT_FAILURE);
		}
	}
	if(close(fd) == -1)
	{
		perror("close()");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}