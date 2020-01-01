#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s source_file dest_file.\n", argv[0]);
		return -1;
	}
	char buf[4096];
	ssize_t bytes;
	// structure to store file stats
	struct stat file_stats;
	// get the file stats of the first file
	if (stat(argv[1], &file_stats) < 0)
	{
		// print error if file doesn't exixst
		perror("stat()");
		exit(EXIT_FAILURE);
	}
	int fd_source = open(argv[1], O_RDONLY);
	int fd_dest = open(argv[2], O_WRONLY | O_EXCL | O_CREAT, file_stats.st_mode);
	if (fd_source < 0 || fd_dest < 0)
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}

	// copy the file from source file to destination file
	while(bytes = read(fd_source, buf, sizeof(buf)))
		if(write(fd_dest, buf, bytes) == -1)
		{
			perror("write()");
			exit(EXIT_FAILURE);
		}

	if(close(fd_source) < 0)
	{
		perror("close()");
		exit(EXIT_FAILURE);
	}
	if(close(fd_dest) < 0)
	{
		perror("close()");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}