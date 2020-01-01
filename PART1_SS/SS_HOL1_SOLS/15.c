#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

extern char **environ;
int main(int argc, char *argv[], char *envp[]){
    int i;
    for (i = 0; envp[i] != NULL; i++)
        printf("\n%s", envp[i]);
    printf("\n");
    return 0;
}

