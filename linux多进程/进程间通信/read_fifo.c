#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    int fd = open("fifo1",O_RDONLY);
    if(fd == -1){
        perror("open");
        exit(0);
    }
    while (1)
    {
        /* code */
        sleep(5);
        char buf[1024] = {0};
        int len = read(fd,buf,sizeof(buf));
        if(len == 0){
            printf("写端无写入\n");
            break;
        }
        printf("rec buf:%s",buf);
    }
    
    close(fd);
    return 0;
}