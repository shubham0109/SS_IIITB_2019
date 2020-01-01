#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

union semun arg;

int main()
{
    int semid, semflag = 0644 | IPC_CREAT | IPC_EXCL;
    int nsems = 1;
    
    int key;
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = -1;
    buf.sem_flg = 0;
    key = ftok(".", (int)'z');
    
    semid = semget(key, nsems, semflag);
    
    arg.val = 2;
    semctl(semid, buf.sem_num, SETVAL, arg);
       
    printf("Before entering to critical section.\n");
    printf("Waiting for lock...\n");
    
    semop(semid, &buf, 1);
        
    printf("Inside critical section.\n");
    printf("Press return to exit critical section.\n");
    getchar();
    buf.sem_op = 1;
    semop(semid, &buf, 1);
    
    return 0;
}

