#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>
#include<sys/time.h>
#include<sys/resource.h>

int main(){

	    int l = getpriority(PRIO_PROCESS,PRIO_USER);
        printf("%d \n",l);

        char c = getchar();
        return 0;
}

