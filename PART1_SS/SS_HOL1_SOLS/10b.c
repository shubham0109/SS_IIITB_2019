#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    int fd = open("file10.txt", O_RDONLY);
    char ch;
    int spaces = 0;
    
    while (read(fd, &ch, 1)){
        if (ch == ' '){
            spaces += 1;
        }
    }
    
    printf("NO. OF SPACES: %d\n", spaces);
    return 0;
}


