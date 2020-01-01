#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
	int fd = open("temp.txt",O_RDONLY);
    int fd1 = creat("temp_copy7.txt",0777);
	
    char buff[50];
	int size = read(fd,buff,50); //read function will return how many byte has been written
	//printf("%s",buff);
	write(fd1,buff,size);
    
    close(fd);
    close(fd1);
	return 0;
}	
