#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    char buff[2] = {'f', 'c'};
    int fd = open("file11.txt", O_RDWR | O_APPEND);
    
    int fcntl_dup = fcntl(fd, F_DUPFD);
    
    int wd;
    
    wd = write(fd, buff, 2);
    printf("wd: %d\n", wd);
    
    wd = write(fcntl_dup, buff, 2);
    printf("wd: %d\n", wd);
    return 0;
}





