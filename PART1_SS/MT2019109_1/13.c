# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/select.h>


int main(){
    
    struct fd_set fd;
    FD_ZERO(&fd); // initializes a descriptor set "fdset" to the null set
    FD_SET(0, &fd); // includes a particular descriptor fd in fdset
    
    struct timeval time;
    time.tv_sec = 10;
    time.tv_usec = 0;
    
    int val = select(1, &fd, NULL, NULL, &time);
    printf("returned value from select: %d\n", val);
    
    if (val == 0){
        printf("No data entered within 10 secs\n");
    }else{
        printf("Data is available now\n");
    }
    
    return 0;
}
