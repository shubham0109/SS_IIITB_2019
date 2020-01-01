#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(){
    int fd1 = open("temp11.txt",O_CREAT|O_RDWR);
    int fd2 = dup(fd1); 
    //printf("fd1:%d fd2:%d",fd1,fd2);
    
    write(fd1,"hii man\n",8);
    write(fd2,"whats upp\n",10);

    int fd3 = dup2(fd1,10);     
    //printf("\nfd1:%d fd3:%d",fd1,fd3);
    
    write(fd3,"Hello World\n",12);

    int fd4 = fcntl(fd1,F_DUPFD,5); 
    int x = fcntl(fd4, F_GETFL);    
    
    write(fd4,"Hello\n",6);
    //printf("\nfd4:%d x:%d",fd4,x);
    return 0;
}

