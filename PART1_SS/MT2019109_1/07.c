#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	char buf[1000];
	int read_fd = open("file_prog7.txt", O_RDONLY);
	int read_ret = read(read_fd, buf, 1024);
	int write_fd = open("file_write7.txt", O_CREAT |  O_RDWR, 0777);
	printf("wr fd: %d\n",write_fd);
	int write_ret = write(write_fd, buf, read_ret);
	
    printf("read return: %d write return : %d\n",read_ret,write_ret);

	return 0;
}
