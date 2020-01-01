#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> // file control
#include <unistd.h> // close 
#include <stdio.h> // printf
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	if(argc != 2)
	{
		fprintf(stderr, "Usage: %s <path_to_create_file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	// create a new file with given permissions and overwrite if file
	// exists 
	int fd = creat(argv[1], S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(fd < 0)
	{
		perror("creat()");
		exit(EXIT_FAILURE);
	}
	printf("The value of the file descriptor: %d\n", fd);
	if(close(fd) < 0)
	{
		perror("close()");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}