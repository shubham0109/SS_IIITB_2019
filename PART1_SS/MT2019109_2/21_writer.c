#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int fd;
    char buf1[512], buf2[512];
    int count;
    while(1)
    {
        fd = open(argv[1], O_WRONLY);
        count = read(STDIN_FILENO, buf1, sizeof(buf1));
        buf1[count] = '\0';
        write(fd, buf1, strlen(buf1) + 1);
        close(fd);
        
        fd = open(argv[1], O_RDONLY);
        read(fd, buf2, sizeof(buf2));
        write(STDOUT_FILENO, buf2, strlen(buf2));
        close(fd);
    }
}

