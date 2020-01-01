#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>
#include<sys/time.h>
#include<sys/resource.h>

int main(){

	char buff[50];
	struct flock l;
	
	int fd=open("temp16.txt",O_RDONLY);
	l.l_type= F_RDLCK;
    l.l_start = 0;
    l.l_whence = SEEK_SET;
    l.l_len = 0;
    l.l_pid = getpid();
	fcntl(fd,F_SETLKW,&l);
	printf("lock file temp16.txt\n");
	int s=read(fd,buff,50);
	printf("Press enter to unlock\n");
    getchar();
	write(1,buff,s);
	l.l_type = F_UNLCK;
 	fcntl (fd, F_SETLKW, &l);
 	close (fd);
	
	return 0;
}
