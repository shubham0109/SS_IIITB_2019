#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>

void show_error(const char *fn_name)
{
    perror(prog);
    exit(EXIT_FAILURE);
}

int main(int argc, char const *argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[1], O_WRONLY);
    
    if(fd < 0) show_error("open()");
    printf("fd is: %d\n", fd);
    // creates a copy of the fd and return the lowest unsed fd for
    // new fd
    // both share the file offset and file status flags
    // FD_CLOEXEC on new fd is off
    int fd1 = dup(fd);
    if(fd1 < 0) show_error("dup()");
    printf("fd1 is: %d\n", fd1);
    off_t offset = 0;
    if(lseek(fd, offset, SEEK_END) < 0 ) show_error("lseek()");
    if(write(fd, "Written at end!\n", 16) < 0) show_error("write()");
    // don't need lseek on fd1 as they have shared offset value
    // if(lseek(fd1, offset, SEEK_END) < 0) show_error("lseek()");
    if(write(fd1, "this is written using fd1 duplicate fd createdby dup().\n", 56) < 0)
        show_error("write()");
    // new fd value given is 6
    int fd2 = 6;
    // if new fd is previously open it closes it silently before
    // reusing it
    fd2 = dup2(fd, fd2);
    if(fd2 < 0) show_error("dup2()");
    printf("fd2 is: %d\n", fd2);
    if(write(fd2, "Written using fd2 duplicate fd created by dup2().\n", 50) < 0)
        show_error("write()");
    // Duplicate the file descriptor fd using the  lowest-numbered
    // available  file  descriptor  greater  than or equal to arg(fd here).
    int fd3 = fcntl(fd, F_DUPFD, fd);
    if (fd3 < 0) show_error("fcntl(fd, F_DUPFD, fd)");
    printf("fd3 is: %d\n", fd3);
    if(write(fd3, "Written using fd3 duplicate fd created by fcntl().\n", 51) < 0)
        show_error("write()");
    
    if(close(fd) < 0 || close(fd1) < 0 || close(fd2) < 0 || close(fd3) < 0)
    {
        perror("close()");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
