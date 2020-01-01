#include<stdio.h>
#include<unistd.h>
#include<limits.h>
int main(void)
{
	long lim;
	lim=sysconf(_SC_OPEN_MAX);
	printf("maximum number of open files %ld",lim);
}
