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

// int sigaction(int __sig, const struct sigaction *__restrict__ __act, struct sigaction *__restrict__ __oact)
// Get and/or set the action for signal SIG.
/*
signum 需要捕捉的信号的编号或者宏值
act捕捉到的信号之后的处理动作
sigaction结构体是
struct sigaction {
               void     (*sa_handler)(int); //函数指针，指向的是信号捕捉到之后的处理函数（signal里面的回调函数）
               void     (*sa_sigaction)(int, siginfo_t *, void *);//函数指针，不常用。
               sigset_t   sa_mask; //临时阻塞信号集，信号捕捉函数执行过程中，临时阻塞某些信号
               int        sa_flags; //使用哪个信号处理函数处理捕捉到的信号，一般是用0 或者sa_siginfo，表示使用第二个回调函数
               void     (*sa_restorer)(void); //已经废弃，指定null
           };

*/

void myAlarm(int num){
    printf("捕捉到的信号的编号是：%d\n",num);
    printf("~~~~~~~~~~~~~~~~~\n");
}

int main(){
    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = myAlarm;
    sigemptyset(&act.sa_mask); //清空

    
    sigaction(SIGALRM,&act,NULL);
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
    while(1){

    }
    return 0;
}