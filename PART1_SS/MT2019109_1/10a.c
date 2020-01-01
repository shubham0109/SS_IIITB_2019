#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    char buf[10] = {'a','b','c','d','e','f','g','h','i','j'};
    int fd = open("file10.txt", O_RDWR);
    int wr = write(fd, buf, 10);
    printf("NO.OF BYTES WRITTEN: %d\n",wr);
    
    int ls = lseek(fd, 10, SEEK_CUR);
    printf("Returned lseek value: %d\n",ls);
    wr = write(fd, buf, 10);
    printf("NO.OF BYTES WRITTEN: %d\n",wr);
    
    return 0;
}

