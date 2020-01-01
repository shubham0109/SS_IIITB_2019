#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


#define ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

int main(int argc, char const *argv[])
{
	int flags = O_RDWR | O_CREAT;
	int mode = S_IRUSR | S_IWUSR; // 0600
	int fd = open("file", flags, mode);
	int ret;
	off_t offset = 0;
	// cur at end
	if((offset = lseek(fd, (off_t)0, SEEK_END)) == (off_t)-1 ) ERR_EXIT("lseek()");
	// cur is zero if file is empty
	if (offset == 0)
	{
	printf("file created new\n");
		int value = 1;
		// write value 1 to file
		if(write(fd, &value, sizeof(int)) == -1) ERR_EXIT("write()");
		printf("Written 1 int to file\n");
		int data;
		while(1)
		{
			if(read(fd, &data, sizeof(data)) == (ssize_t)0) break;
			printf("element: %d\n", data);
		}
		return 0;
	}
	else
	{
		// file is not empty before
		if((ret = lseek(fd, (off_t)-(sizeof(int)), SEEK_END)) == -1) perror("lseek()");
		printf("return value %d\n", ret);
		printf("offset modified%ld\n", (off_t)-(sizeof(int)));
		int first = 5, second, data; 
		read(fd, &first, sizeof(int));
		second = first + 1;
		write(fd, &second, sizeof(int));
		// lseek(fd, 0L, SEEK_END);
		// second = 80;
		// write(fd, &second, sizeof(int));

		// curser at beggining
		lseek(fd, 0L, SEEK_SET);
		while(1)
		{
			if(read(fd, &data, sizeof(data)) == (ssize_t)0) break;
			printf("element: %d\n", data);
		}

    }


	return 0;
}