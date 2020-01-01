#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>

int main(){
    int fd = open("temp.txt",O_RDONLY);
    int mode=fcntl(fd,F_GETFL);
    mode = mode & O_ACCMODE;
    if(mode == 0)
        printf("read only\n");
    else if(mode == 1)
        printf("write only\n");
    else
        printf("read write\n");

    return 0;
}
