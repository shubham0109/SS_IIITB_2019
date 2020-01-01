#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void show_error(const char *fn_name)
{
	perror(fn_name);
	exit(EXIT_FAILURE);
}

int main(int argc, char const *argv[])
{
	if(argc != 2)
	{
		fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int fd = open(argv[1], O_CREAT | O_RDONLY | O_EXCL,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(fd < 0) show_error("open()");
	int flag_val = fcntl(fd, F_GETFL);
	if(flag_val < 0) show_error("fcntl()");

	printf("Opening mode: ");
	
	if((flag_val & O_ACCMODE) == O_RDONLY) 
		printf("O_RDONLY\n");

	if((flag_val & O_ACCMODE) == O_WRONLY) 
		printf("O_WRONLY\n");
	
	if((flag_val & O_ACCMODE) == O_RDWR)
		printf("O_RDWR\n");
	if(close(fd) < 0)
	{
		perror("close()");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}