#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	int read_fd = open("file_prog7.txt", O_RDONLY);
	//int write_fd = open("write8.txt", O_CREAT | O_WRONLY);
	char ch;

	while(read(read_fd, &ch, 1)){
		write(1, &ch, 1);
	}
}
