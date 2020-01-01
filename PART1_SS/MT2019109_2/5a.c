#include<stdio.h>
#include<unistd.h>
#include<limits.h>
int main(void)
{
	long lim;
	lim=sysconf(_SC_ARG_MAX);
	printf("maximum length of arguments to the exec family of functions is %ld",lim);
}
