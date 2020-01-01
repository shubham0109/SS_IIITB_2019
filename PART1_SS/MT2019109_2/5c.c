#include<stdio.h>
#include<unistd.h>
#include<limits.h>
int main(void)
{
	long lim;
	lim=sysconf(_SC_CLK_TCK);
	printf("number of clock ticks (jiffy) per second is %ld",lim);
}
