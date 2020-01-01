#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s file_name\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	char buf[1024];
	int fd = open(argv[1], O_RDONLY);
	if(fd < 0)
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}

	while(read(fd, buf, 1))
	{
		if(buf[0] == '\n') getchar();
		else printf("%c", buf[0]);
	}
	if(close(fd) < 0)
	{
		perror("close()");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}