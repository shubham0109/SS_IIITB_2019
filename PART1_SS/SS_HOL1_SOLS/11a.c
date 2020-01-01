#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    char buff[2] = {'a', 'b'};
    int fd = open("file11.txt", O_RDWR | O_APPEND);
    
    int dup_fd = dup(fd);
    
    
    write(fd, buff, 2);
    write(dup_fd, buff, 2);
    return 0;
}



