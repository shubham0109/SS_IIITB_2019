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

	struct flock l;
	l.l_whence=SEEK_SET;
	l.l_len=sizeof(database);
	l.l_pid=getpid();

	int fd=open("database18", O_RDWR);
    printf("Press 1 to read a record \n");
    printf("Press 2 to update a record\n");
    printf("Press 3 to exit\n");
			
    while(1){
		int choice,temp=0,b;
		scanf("%d",&choice);
        
        switch(choice){
            case 1:
                printf("Select ticketno from 0 to 2\n");
               	scanf("%d",&b);
	    		l.l_type=F_RDLCK;
	    		l.l_start=(b)*sizeof(database);
	    		fcntl(fd, F_SETLKW, &l);
	    		lseek(fd, l.l_start, SEEK_SET);
	    		read(fd, &database, sizeof(database));
	    		printf("Ticket No. : %d\n", database.ticketno);
                printf(" Press to unlock\n");
                getchar();
                l.l_type=F_UNLCK;
        		fcntl(fd,F_SETLK, &l);
                break;
            case 2:
                printf("select record no from 0 to 2\n");
                scanf("%d",&b);
	    		l.l_type=F_WRLCK;
	    		l.l_start=(b)*sizeof(database);
	    		fcntl(fd, F_SETLKW, &l);
	    		lseek(fd, l.l_start, SEEK_SET);
	    		read(fd, &database, sizeof(database));
    
	    		database.ticketno++; //can do any modification here
	    		
                lseek(fd, l.l_start, SEEK_SET);
	    		write(fd,&database, sizeof(database));
	    		printf("Ticket No. : %d\n", database.ticketno);
                printf(" Press to unlock\n");
                getchar();
                l.l_type=F_UNLCK;
        		fcntl(fd,F_SETLK, &l);
                break;
            case 3:
                temp = 1;
                break;
        }
        if(temp == 1)
            break;
	}
	return 0;
}
