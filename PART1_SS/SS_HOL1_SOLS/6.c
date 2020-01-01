#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main(){
    int n=5;  // scanf("%d",&n); //(take input on size of string;)
	char buff[n]; 
	
    read(0,buff,n); //read from terminal STDIN
   
   	write(1,buff,strlen(buff)); //write on terminal STDOUT

	return 0;
}
