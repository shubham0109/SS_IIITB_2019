#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	struct stat file_stat;	
	stat(argv[1],&file_stat);
	unsigned int type =file_stat.st_mode;
    if(S_ISSOCK(type))
		printf("Socket\n"); 			
	else if(S_ISLNK(type))
		printf("Symbolic link\n"); 		 
	else if(S_ISREG(type))
		printf("Regular File\n");
	else if(S_ISBLK(type))
		printf("Block device\n"); 		 
	else if(S_ISDIR(type))
		printf("Directory\n"); 
	else if(S_ISCHR(type))
		printf("Character device\n"); 		
	else if(S_ISFIFO(type))
		printf("FIFO (named pipe)\n"); 		
	else
		printf("Invalid File\n");			
    
    return 0;
}

/*
get the details from 
man 7 inode
*/
