#include<stdio.h>
#include<unistd.h>
#include<limits.h>
int main(void)
{
	long lim;
	lim=sysconf(_SC_CHILD_MAX);
	printf("The maximum number of simultaneous process(child) per user id is %ld",lim);
}
