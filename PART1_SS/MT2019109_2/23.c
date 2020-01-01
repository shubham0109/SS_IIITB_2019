#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    long PIPE_BUF, OPEN_MAX;
    PIPE_BUF = pathconf(".", _PC_PIPE_BUF);
    OPEN_MAX = sysconf(_SC_OPEN_MAX);
    printf("Maximum number of bytes that can be written atomically to a pipe of FIFO: %ld bytes\n", PIPE_BUF);
    printf("Maximum number of files that can be opened by proces: %ld\n", OPEN_MAX);
    
    return 0;
}

