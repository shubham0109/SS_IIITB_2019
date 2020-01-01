#include <stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main()
{
    int fd1,fd2,fd3,fd4,fd5;
    fd1 = open("temp51.txt",O_CREAT | O_RDONLY,0744);
    fd2 = open("temp52.txt",O_CREAT | O_WRONLY,0744);
    fd3 = open("temp53.txt",O_CREAT | O_RDONLY,0744);
    fd4 = open("temp54.txt",O_CREAT | O_RDONLY,0744);
    fd5 = open("temp55.txt",O_CREAT | O_RDONLY,0744);
        
    getchar();
    return 0;
}

// remaining
