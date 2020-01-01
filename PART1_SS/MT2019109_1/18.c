# include <stdio.h>
# include <sys/file.h>
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>


int main(){
    
    int fd;
    struct {
        int key;
    }node1, node2, node3;
    
    node1.key = 200;
    node2.key = 400;
    node3.key = 800;
    fd = open("db18", O_CREAT | O_RDWR, 0744);
    write(fd, &node1, sizeof(node1));
    write(fd, &node2, sizeof(node2));
    write(fd, &node3, sizeof(node3));
    close(fd);
    
    fd = open("db18", O_RDONLY);
    read(fd, &node1, sizeof(node1));
    printf("key: %d\n", node1.key);
    read(fd, &node2, sizeof(node2));
    printf("key: %d\n", node2.key);
    read(fd, &node3, sizeof(node3));
    printf("key: %d\n", node3.key);
    close(fd);
    
    return 0;
}
