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

	fd=open("database18", O_CREAT|O_RDWR, 0744);
	database.ticketno=101;
	write(fd, &database, sizeof(database));
	database.ticketno=202;
	write(fd, &database, sizeof(database));
	database.ticketno=303;
	write(fd, &database, sizeof(database));
	close(fd);

}
