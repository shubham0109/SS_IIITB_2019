#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
    int msgid;
    int size;
    int key;
    
    struct msg
    {
        long mtype;
        char message[80];
    }mq;
    
    key = ftok(".", (int)'a');
    msgid = msgget(key, 0644 | IPC_CREAT);
    printf("Enter the message type: ");
    scanf("%ld", &(mq.mtype));
    printf("Enter the message: ");
    scanf("%s", mq.message);
    size = strlen(mq.message);
    
    msgsnd(msgid, &mq, size + 1, 0);
    
    printf("Data sent successfully to message queue.\n");
    printf("msgid: %d, message type: %ld and size: %d.\nmessage: %s\n", msgid, mq.mtype, size, mq.message);
    
    return 0;
}

