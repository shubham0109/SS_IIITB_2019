#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>

int main(){
    int fd;
    fd = open("temp.txt",O_RDWR); //open file in read-write mode
    //fd = open("temp4.txt",O_CREAT |O_EXCL); //O_EXCL will give error if your file already exists.   
    printf("%d",fd);
    close(fd);
    return 0;
}
