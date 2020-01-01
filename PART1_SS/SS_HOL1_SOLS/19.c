#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>

int main(){
        int fd = open("text.txt",744);
	    clock_t tf = clock();
	    int l = getpid();
        clock_t tl = clock();
        printf("%ld ms to run getpid\n",tl-tf);
        return 0;
}

