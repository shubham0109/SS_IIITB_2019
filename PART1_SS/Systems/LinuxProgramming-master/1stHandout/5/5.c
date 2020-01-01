#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	int flags = O_RDWR | O_CREAT;
	int mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	int fd1 = open("file1", flags, mode);
	int fd2 = open("file2", flags, mode);
	int fd3 = open("file3", flags, mode);
	int fd4 = open("file4", flags, mode);
	int fd5 = open("file5", flags, mode);
	if(fd1 < 0 || fd2 < 0 || fd3 < 0 || fd4 < 0 || fd5 < 0)
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}
	printf("File descriptor of the opened file1: %d\n", fd1);
	printf("File descriptor of the opened file1: %d\n", fd2);
	printf("File descriptor of the opened file1: %d\n", fd3);
	printf("File descriptor of the opened file1: %d\n", fd4);
	printf("File descriptor of the opened file1: %d\n", fd5);
	while(1);
	if(close(fd1) < 0 || close(fd2) < 0 || close(fd3) < 0 || close(fd4) < 0 || close(fd5) < 0)
	{
		perror("close()");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
