#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>

int main(){
    int fd;
    fd = creat("temp3.txt",777); //777 is permissions for file;
    printf("%d\n",fd);
    return 0;
}
