#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	if(argc != 3)
	{
		fprintf(stderr, "Usage: %s <file_name> <ticket_number>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(fd < 0)
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}
	struct ticket_st
	{
		long long int ticket_number;
	}ticket_st;
	ticket_st.ticket_number = atoll(argv[2]);
	if(write(fd, &ticket_st, sizeof ticket_st) < 0)
	{
		perror("write()");
		exit(EXIT_FAILURE);
	}
	if(close(fd) < 0)
	{
		perror("close()");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}