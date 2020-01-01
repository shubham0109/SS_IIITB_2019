#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

int main()
{
    struct rlimit rlim, rlim1;
    printf("Value of core file size before changing: ");
    getrlimit(RLIMIT_CORE, &rlim);
    printf("%llu\n", rlim.rlim_cur);
    printf("Value of core file size after changing: ");
    rlim.rlim_cur = 1024;
    setrlimit(RLIMIT_CORE, &rlim);
    getrlimit(RLIMIT_CORE, &rlim1);
    printf("%llu\n", rlim1.rlim_cur);
    
    return 0;
}

