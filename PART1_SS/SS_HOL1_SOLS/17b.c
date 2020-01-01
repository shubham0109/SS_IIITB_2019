#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/resource.h>
#include <stdlib.h>
#include<string.h>

int main(){
    struct{
		int ticketno;
	} database;
	
    int fd=open("database1",O_RDWR);
	struct flock l;
	
    l.l_type=F_WRLCK;
    l.l_whence=SEEK_SET;
	l.l_start=0;
	l.l_len=0;
	l.l_pid=getpid();

	fcntl(fd,F_SETLKW,&l); //apply write lock
	
    //read(fd,buff,20); 
    //int ticket = atoi (buff);
    read(fd,&database,sizeof(database));    

    printf("Ticket number before %d\n",database.ticketno);
	
    database.ticketno++; //critical section

	printf("Ticket number after%d\n",database.ticketno);
	lseek (fd,0L,SEEK_SET);
	//write(fd,buff,strlen(buff));
    write(fd,&database,sizeof(database));

	printf("Press enter to unlock");
	getchar();
	l.l_type = F_UNLCK;
    fcntl (fd, F_SETLKW, &l);
    close(fd);
	
    return 0;
}



