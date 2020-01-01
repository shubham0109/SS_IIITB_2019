# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/file.h>
# include <unistd.h>

int main(){
    
    
    int fd; char ch, c;
    struct{
        int data;
    }node;
    
    fd = open("database", O_CREAT|O_RDWR, 0777);
    
    node.data = 100;
    
    write(fd, &node, sizeof(node));
    printf("enter 0 to write and 1 to read\n");
    read(0, &ch, sizeof(ch));
    
    // write lock
    if (ch == '0'){
        flock(fd, 2);
        node.data *= 1.5;
        write(fd, &node, sizeof(node));
        
        printf("Press enter to unlock: ");
        getchar();
        getchar();
        flock(fd, 8);
        
    }else{
        // read lock
        flock(fd, 1);
        printf("READING\n");
        read(fd, &node, sizeof(node));
        printf("data: %d\n", node.data);
        
        printf("Press Enter to unlock: ");
        getchar();
        getchar();
        flock(fd, 8);
    }
    
    
    return 0;
}
