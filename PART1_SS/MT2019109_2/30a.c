#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
    int shmid, shmflag = 0644 | IPC_CREAT;
    size_t size = 1024;
    key_t key;
    char *data;
    
    key = ftok(".", (int)'a');
    
    shmid = shmget(key, size, shmflag);
    data = (char*)shmat(shmid, NULL, shmflag);
    printf("Enter the data you want to write to shared memomry: ");
    scanf(" %[^\n]", data);
    printf("Data: %s\n", data);
    if(shmdt(data) == -1){
        printf("error in writing\n");
        exit(0);
    }
    
    return 0;
}

