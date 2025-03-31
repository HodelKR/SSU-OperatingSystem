#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char **argv){
    int fd;
    if(argc < 4){
        printf(1, "usage : lseek_test <filename> <offset> <string>\n");
        exit();
    }

    fd = open(argv[1], O_RDWR);
    if(fd < 0){
        printf(1, "no such file\n");
        exit();
    }

    char buf[256];
    int n=0;
    if((n=read(fd, buf, sizeof(buf)-1)) > 0){
        buf[n] = '\0';
        printf(1, "Before : %s\n", buf);
    }
    
    lseek(fd, atoi(argv[2]), 0);
    write(fd, argv[3], strlen(argv[3]));
    close(fd);

    fd = open(argv[1], O_RDONLY);
    if(fd < 0){
        printf(1, "no such file\n");
        exit();
    }

    if((n=read(fd, buf, sizeof(buf)-1)) > 0){
        buf[n] = '\0';
        printf(1, "After : %s\n", buf);
    }
    close(fd);

    exit();
}