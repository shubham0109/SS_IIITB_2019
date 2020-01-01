#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int fd = open(argv[1], O_RDWR);
	if(fd < 0)
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	// for advisory file locking both should be 0
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_pid = getpid();
	printf("Aquiring lock.\n");
	if(fcntl(fd, F_SETLKW, &lock)< 0)
	{
		perror("fcntl()");
		exit(EXIT_FAILURE);
	}
	printf("Write lock is aquired.\n");
	printf("In the critical section.\n");
	printf("Press any key to exit the lock.\n");
	getchar();
	lock.l_type = F_UNLCK;
	if(fcntl(fd, F_SETLKW, &lock))
	{
		perror("fcntl()");
		exit(EXIT_FAILURE);
	}
	printf("Unlocked the file.\n");
	if(close(fd) < 0)
	{
		perror("close()");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}