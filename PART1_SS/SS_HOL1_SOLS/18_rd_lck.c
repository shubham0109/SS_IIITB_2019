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
    
    printf("Acquiring read lock\n");
    flock(fd, 1);
    
    read(fd, &node1, sizeof(node1));
    printf("key: %d\n", node1.key);
    read(fd, &node2, sizeof(node2));
    printf("key: %d\n", node2.key);
    read(fd, &node3, sizeof(node3));
    printf("key: %d\n", node3.key);
    printf("press enter to unlock\n");
    getchar();
    flock(fd, 8);
}

