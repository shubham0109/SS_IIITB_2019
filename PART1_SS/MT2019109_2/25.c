#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    struct msqid_ds msq;
    
    msgctl(atoi(argv[1]), IPC_STAT, &msq);

    printf ("%d\n",msq.msg_perm.mode);
    printf ("%d\n",msq.msg_perm.uid);
    printf ("%d\n",msq.msg_perm.gid);
    printf ("%lu\n",msq.msg_qbytes);
    printf ("%lu\n",msq.msg_stime);
    
    return 0;
}

