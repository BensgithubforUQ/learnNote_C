#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){
    int fd = open("fifo1",O_WRONLY);
    if(fd == -1){
        perror("open");
        exit(0);
    }
    for(int i =0;i<100;i++){
        char buf[1024] = {0};
        sprintf(buf,"hello：%d \n",i);
        write(fd,buf,strlen(buf));
        sleep(1);
    }
    close(fd);
    return 0;
}