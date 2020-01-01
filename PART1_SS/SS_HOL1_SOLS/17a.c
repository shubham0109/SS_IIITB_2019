#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/resource.h>
#include <stdlib.h>
#include<string.h>


int main(){
	int fd;
	struct{
		int ticketno;
	} database;

	fd=open("database1", O_CREAT|O_RDWR, 0744);
	database.ticketno=101;
	write(fd, &database, sizeof(database));
	close(fd);
}




/* not be helful use stuct instead
int main(){	
   
	int fd = open("ticket.txt",O_CREAT | O_RDWR,0744);
	write(fd,"20",2);
	close(fd);
	return 0;
}*/


