#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

int main()
{
    int key;
    key = ftok(".", (int)'a');
    int msgid;
    msgid = msgget(key, 0644 | IPC_CREAT);
    printf("key = %d\n", key);
    printf("msgid = %d\n", msgid);
    
    return 0;
}

