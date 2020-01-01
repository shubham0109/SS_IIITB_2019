#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void show_error(const char* fn_name)
{
    perror(fn_name);
    exit(EXIT_FAILURE);
}

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int fd;
	fd = open(argv[1], O_CREAT | O_WRONLY | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(fd < 0) show_error("open()");
	if(write(fd, "Software--", 10) < 0) show_error("write()");
	off_t ret_val;
	if((ret_val = lseek(fd, 10L, SEEK_CUR)) < 0) show_error("lseek()");
	printf("Return value of lseek(): %lu\n", ret_val);
	if(write(fd, "Systems !\n", 10) < 0) show_error("write()");
	if(close(fd) < 0)
	{
		perror("close()");
		exit(EXIT_FAILURE);
	}
	return 0;
}
