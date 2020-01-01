#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int fd = open(argv[1], O_RDWR);
	if(fd == -1)
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_pid = getpid();
	if(fcntl(fd, F_SETLKW, &lock)< 0)
	{
		perror("fcntl()");
		exit(EXIT_FAILURE);
	}
	struct ticket_st
	{
		long long int ticket_number;
	}ticket_st;
	int count = read(fd, &ticket_st, sizeof ticket_st);
	if(count == -1)
	{
		perror("read()");
		exit(EXIT_FAILURE);
	}
	if(ftruncate(fd, 0) == -1)
	{
		perror("ftruncate()");
		exit(EXIT_FAILURE);
	}
	
	ticket_st.ticket_number++;

	if(lseek(fd, 0L, SEEK_SET) < 0)
	{
		perror("lseek()");
		exit(EXIT_FAILURE);
	}
	if(write(fd, &ticket_st, sizeof ticket_st) < 0)
	{
		perror("write()");
		exit(EXIT_FAILURE);
	}

	printf("Incremented successfully.\n");
	printf("New ticket number: %lld\n", ticket_st.ticket_number);

	lock.l_type = F_UNLCK;
	if(fcntl(fd, F_SETLKW, &lock))
	{
		perror("fcntl()");
		exit(EXIT_FAILURE);
	}
	if(close(fd) < 0)
	{
		perror("close()");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}