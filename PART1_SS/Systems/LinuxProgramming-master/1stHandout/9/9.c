#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <stdlib.h> // exit()
#include <time.h> // ctime()

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	struct stat file_stats;
	if(stat(argv[1], &file_stats) < 0)
	{
		perror("stat()");
		exit(EXIT_FAILURE);
	}
	printf("Inode number: %ld\n", (long)file_stats.st_ino);
	printf("Number of hard links: %ld\n", (long)file_stats.st_nlink);
	printf("User ID of owner: %ld\n", (long)file_stats.st_uid);
	printf("Group ID of owner: %ld\n", (long)file_stats.st_gid);
	printf("Total size: %lld bytes\n", (long long)file_stats.st_size);
	printf("Block size for FS I/O: %ld\n", (long)file_stats.st_blksize);
	printf("Number of 512B blocks allocated: %lld\n", (long long)file_stats.st_blocks);
	printf("Time of last access: %s", ctime(&file_stats.st_atime));
	printf("Time of last modification:  %s", ctime(&file_stats.st_mtime));
	printf("Time of last change: %s", ctime(&file_stats.st_ctime));
	exit(EXIT_SUCCESS);
}