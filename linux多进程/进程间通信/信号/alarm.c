#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

int main(){
    // unsigned int alarm(unsigned int seconds);
    /*
    倒计时结束会给当前进程发送一个信号sigalarm
    seconds倒计时时长。单位秒，参数有为0，计时器无效
    返回值，倒计时剩余时间
    sigalarm每个进程有且只有一个定时器
    */
    int sec = alarm(5);
    printf("seconds = %d \n",sec);
    sleep(2);
    sec = alarm(10); //不阻塞
    printf("seconds = %d \n",sec);
    while(1){
        //死循环
    }
    return 0;
}