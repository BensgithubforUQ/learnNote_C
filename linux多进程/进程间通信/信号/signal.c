#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>

void myAlarm(int num);//回调函数


int main()
{
    // typedef void (*sighandler_t)(int);

    // sighandler_t signal(int signum, sighandler_t handler);
    // sigkill,sigstop 不能被捕捉或者忽略
    //功能，设置某个信号的捕捉行为
    /*
    signum要捕捉的信号。
    handler捕捉到信号的时候，处理的方法。
        -sigign，忽略信号
        -sig_dfl，使用信号的默认行为
        -回调函数，调用函数，内核调用，程序员只负责写。
    返回值：成功了，返回前一次回调函数。
    失败了，返回sig_err,设置erronumber
    */
    //注册信号捕捉
    //signal(SIGALRM,SIG_IGN);//忽略信号，那就会无限的进行下去，不会停止进程

    //signal(SIGALRM,SIG_DFL);//默认，就是没有捕获
    signal(SIGALRM,myAlarm);

    // int setitimer(int which, const struct itimerval *new_value, struct itimerval *old_value);
    struct itimerval new_value;
    new_value.it_interval.tv_sec = 2; //持续时间
    new_value.it_interval.tv_usec = 0;

    new_value.it_value.tv_sec = 3; //延迟
    new_value.it_value.tv_usec = 0;

    int ret = setitimer(ITIMER_REAL, &new_value, NULL); //非阻塞
    if (ret == -1)
    {
        perror("setitimer");
        exit(0);
    }
    getchar();
    return 0;
}

void myAlarm(int num){
    printf("捕捉到的信号的编号是：%d\n",num);
    printf("~~~~~~~~~~~~~~~~~\n");
}