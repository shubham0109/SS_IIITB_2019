#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    char buff[2] = {'s', 'k'};
    int fd = open("file11.txt", O_RDWR | O_APPEND);
    int fd2 = open("file11.txt", O_RDWR | O_APPEND);
    fd2 = fd;
    int dup_fd = dup2(fd, fd2);
    
    
    write(fd, buff, 2);
    write(dup_fd, buff, 2);
    return 0;
}




