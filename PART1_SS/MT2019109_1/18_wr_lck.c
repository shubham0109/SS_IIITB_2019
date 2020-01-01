# include <stdio.h>
# include <sys/file.h>
# include <unistd.h>
# include <fcntl.h>


int main(){
    int fd;
    struct{
        int key;
    }node1, node2, node3;
    
    fd = open("db18", O_RDWR, 0744);
    
    printf("Acquiring write lock\n");
    flock(fd, 2);
    node1.key = 50;
    node2.key = 80;
    write(fd, &node1, sizeof(node1));
    write(fd, &node2, sizeof(node2));
    printf("press enter to unlock\n");
    getchar();
    flock(fd, 8);
}
