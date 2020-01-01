#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>
#include<sys/time.h>
#include<sys/resource.h>

int main(char **argc){

	struct flock l;
	
	int fd=open("temp16.txt",O_WRONLY);
	
	l.l_type= F_WRLCK;
    l.l_start = 0;
    l.l_whence = SEEK_SET;
    l.l_len = 0;
    l.l_pid = getpid();
	
    fcntl(fd,F_SETLKW,&l);
	
    printf("file is locked for write \n");
	write(fd,"HELLO\n",6); //you can write here 
	printf("Press any character to unlock\n");
	getchar();
	
	l.l_type = F_UNLCK;
 	fcntl (fd, F_SETLKW, &l);
 	close (fd);
 	return 0;
}
