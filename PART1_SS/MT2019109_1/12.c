#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    
    int fd = open("file11.txt", O_RDWR | O_APPEND);
    
    int fcntl_val = fcntl(fd, F_GETFL);
    
    printf("the val returned is: %d\n", fcntl_val);
    return 0;
}
