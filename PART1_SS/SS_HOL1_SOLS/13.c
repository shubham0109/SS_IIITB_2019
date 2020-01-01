#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(){

    fd_set fd;
    FD_ZERO(&fd);
    FD_SET(0,&fd);

    struct timeval time;
    time.tv_sec = 10;
    time.tv_usec = 0;

    int value = select(1,&fd,NULL,NULL,&time);
    printf("Return from select: %d\n",value);
    if (value == 0)
        printf("No data within ten seconds.\n");
    else
        printf("Data is available now.\n");

    return 0;
}



