# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>

int main(){
    
    int fd = open("file11.txt", O_RDWR, 0777);
    char buff[2] = {'2', '5'};
    
    fork();
    int wr = write(fd, buff, strlen(buff));
    printf("wr: %d\n", wr);
    
    return 0;
}
