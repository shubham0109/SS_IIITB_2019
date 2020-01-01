# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/stat.h>


int main(){
    int fd;
    struct flock lock;
    struct {
        int tno;
    }adm;
    
    fd = open("database", O_RDWR, 0744);
    read(fd, &adm, sizeof(adm));
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();
    printf("Before entering CS:\n");
    fcntl(fd, F_SETLKW, &lock);
    printf("Ticket No. : %d", adm.tno);
    adm.tno++;
    lseek(fd, 0L, SEEK_SET);
    printf("\nInside the CS:\n");
    write(fd, &adm, sizeof(adm));
    printf("Press Entr to Unlock: ");
    getchar();
    lock.l_type = F_UNLCK;
    printf("\nunlocked\n");
    fcntl(fd, F_SETLK, &lock);
    printf("finished processing");
    return 0;
}
