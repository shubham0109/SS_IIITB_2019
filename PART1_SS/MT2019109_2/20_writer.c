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
    ssize_t count;
    while(1)
    {
        fd = open(argv[1], O_WRONLY);
        count = read(STDIN_FILENO, buf, sizeof(buf));
        buf[count] = '\0';
        write(fd, buf, strlen(buf) + 1);
        close(fd);
        if(strcmp(buf, "exit\n") == 0) exit(0);
        
    }
}

