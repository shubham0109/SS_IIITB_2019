#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
	int fd = open("temp10.txt",O_RDWR | O_CREAT);
	
    char buff[10] = "hello man";
	write(fd,buff,10);

	int i = lseek(fd,10,SEEK_CUR); //this will take pointer to 5 step back from current position
	printf("ret value of lseek:%d \n",i);
    
    char buff2[10] = "loooser";
	write(fd,buff2,10);
	
    close(fd);
	return 0;
}

/*
$od -c filename
*/ 
