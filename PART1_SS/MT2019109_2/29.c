#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    
    printf("Removing msgq with msgid: %s\n", argv[1]);
    msgctl(atoi(argv[1]), IPC_RMID, NULL);
    printf ("msgq removed successfully.\n");
    return 0;
}

