# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

int main(){
    
    int fd = open("file11.txt", O_RDWR | O_EXCL, 0777);
    printf("file descriptor %d", fd);
    
    return 0;
}
