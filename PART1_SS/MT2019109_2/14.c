#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int fd[2];
    char buf[10];
    pipe(fd);
    write(fd[1], "Hello\0", 5);
    read(fd[0], buf, sizeof(buf));
    printf("Read from Pipe: %s\n", buf);
    
    return 0;
}

