#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
    char buff[50];
    int fd = open("temp.txt",O_RDONLY); //open file in read only mode

    int i=0;
    while(read(fd,&buff[i],1) != 0){   //we read data one by one byte until reach EOF.
        if(buff[i] == '\n'){            //whenever encounter next line symbol we write.
            write(1,buff,i+1);
            i=0;
        }else{
            i++;        //i keep track of size of line.
        }
    }
    close(fd);
	return 0;
}
