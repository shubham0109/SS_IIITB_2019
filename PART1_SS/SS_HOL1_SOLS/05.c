# include <stdio.h>
# include <fcntl.h>

int main(){
    
    int fd1 = open("file5a.txt", O_CREAT | O_RDWR, 0777);
    int fd2 = open("file5b.txt", O_CREAT | O_RDWR, 0777);
    int fd3 = open("file5c.txt", O_CREAT | O_RDWR, 0777);
    int fd4 = open("file5d.txt", O_CREAT | O_RDWR, 0777);
    int fd5 = open("file5e.txt", O_CREAT | O_RDWR, 0777);
    
    return 0;
}
