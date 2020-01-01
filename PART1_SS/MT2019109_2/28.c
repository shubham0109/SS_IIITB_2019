#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#define ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

int main(int argc, char const *argv[])
{
    
    struct msqid_ds msq;
    
    msgctl(atoi(argv[1]), IPC_STAT, &msq);
    
    printf ("The access permissions before modification = 0%o\n",msq.msg_perm.mode);
    
    msq.msg_perm.mode = (unsigned short)strtol(argv[2], NULL, 8);
    msgctl(atoi(argv[1]), IPC_SET, &msq);
    
    msgctl(atoi(argv[1]), IPC_STAT, &msq);
    
    printf ("The access permissions after modification = 0%o\n",msq.msg_perm.mode);
    
    return 0;
}

