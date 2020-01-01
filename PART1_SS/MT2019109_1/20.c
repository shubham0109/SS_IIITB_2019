# include <stdio.h>
# include <unistd.h>
# include <sys/resource.h>

int main(){
    int pr_old = getpriority(PRIO_PROCESS,0);
    printf("priority: %d\n", pr_old);
    int pr_new = nice(5);
    printf("priority: %d\n", pr_new);
    
    return 0;
}
