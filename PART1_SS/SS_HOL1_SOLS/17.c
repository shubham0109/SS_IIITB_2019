# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/stat.h>

int main(){
    int fd;
    struct {
        int tno;
    }adm;
    
    adm.tno = 10;
    fd = open("database", O_CREAT|O_RDWR, 0744);
    write(fd, &adm, sizeof(adm));
    close(fd);
    fd = open("database",O_RDONLY);
    read(fd,&adm,sizeof(adm));
    printf("TICKET NO. : %d", adm.tno);
    close(fd);
    
    return 0;
}
