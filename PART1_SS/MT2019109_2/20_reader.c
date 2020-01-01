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
    char buf[512];
    while(1)
    {
        fd = open(argv[1], O_RDONLY);
        read(fd, buf, sizeof(buf));
        write(STDOUT_FILENO, buf, strlen(buf));
        close(fd);
        if(strcmp(buf, "exit\n") == 0) exit(0);
    }
}

