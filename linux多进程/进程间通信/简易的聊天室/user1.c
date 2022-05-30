#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){
    //1.判断有名管道是否存在
    int f1 = access("fifo1",F_OK);
    if(f1 == -1){
        int ret = mkfifo("fifo1",0664);
        if(ret == -1){
            perror("mkfifo");
            exit(0);
        }
    }
    int f2 = access("fifo2",F_OK);
    if(f2 == -1){
        int ret = mkfifo("fifo2",0664);
        if(ret == -1){
            perror("mkfifo");
            exit(0);
        }
    }
    f1 = open("fifo1",O_WRONLY);
    printf("f1打开成功...");
    f2 = open("fifo2",O_RDONLY);
    printf("f2打开成功...");
    char buf[128];
    while(1){
        //获取标准输入的数据
        //memset(buf,0,128);
        fgets(buf,128,stdin);
        //写数据
        write(f1,buf,strlen(buf));

        //memset(buf,0,128);
        //读数据
        int ret = read(f2,buf,128);
        printf("buf:%s\n",buf);
    }
    close(f1);
    close(f2);
    return 0;
}