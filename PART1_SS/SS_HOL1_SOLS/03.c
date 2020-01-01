# include <stdio.h>
# include <fcntl.h>

int main(){
    
    int fd = creat("file3.txt", O_RDWR);
    printf("the file descriptor value is %d\n", fd);
    
    return 0;
}
