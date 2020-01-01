#include <stdio.h> // printf function
#include <sys/types.h> // data types
#include <sys/stat.h> 
#include <fcntl.h> // file control
#include <unistd.h> // for close function
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	if(argc != 2)
	{
		fprintf(stderr, "Usage: %s /read_file_path\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	// open file in read write mode 
	// if file doesn't exist create the file and if file exist 
	// through error file already exist(EEXIST)
	// int fd = open(argv[1], O_RDWR | O_EXCL | O_CREAT, 0644);
	
	// open file in read write mode if file doesn't exist return
	// an error no such file or directory
	// int fd = open(argv[1], O_RDWR | O_EXCL);

	// open file in read write mode if file doesn't exist return
	// an error no such file or directory
	// int fd = open(argv[1], O_RDWR);
	
	// open file in read write form if exist and else first create 
	// the file then opens it in read write mode
	int fd = open(argv[1], O_RDWR | O_CREAT, 0644);

	if(fd < 0)
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}
	printf("File descriptor of the opened file: %d\n", fd);
	if(close(fd) < 0)
	{
		perror("close()");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
