#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
    int msgid;
    int key;
    long msgtype = 0;
    struct msg
    {
        long mtype;
        char message[80];
    }mq;
    
    key = ftok(".", (int)'a');
    msgid = msgget(key, 0644 | IPC_CREAT);
    
    msgrcv(msgid, &mq, sizeof(mq), msgtype, 0);
    
    printf("message: %s\n", mq.message);
    
    return 0;
}

