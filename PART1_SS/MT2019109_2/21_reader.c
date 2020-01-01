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
    ssize_t count;
    while(1)
    {
        fd = open(argv[1], O_RDONLY);
        read(fd, buf1, sizeof(buf1));
        write(STDOUT_FILENO, buf1, strlen(buf1));
        close(fd);
        
        fd = open(argv[1], O_WRONLY);
        count = read(STDIN_FILENO, buf2, sizeof(buf2));
        buf2[count] = '\0';
        write(fd, buf2, strlen(buf2) + 1);
        close(fd);
    }
}

