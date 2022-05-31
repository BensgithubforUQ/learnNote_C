#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>
#include <string.h>

void work(int num){
    time_t t = time(NULL);
    struct tm * loc = localtime(&t);
    char buf[1024];
    sprintf(buf,"%d-%d-%d %d:%d:%d\n",
    loc->tm_year,loc->tm_mon,loc->tm_mday,loc->tm_hour,loc->tm_min,loc->tm_sec);
    printf("%s\n",buf);
    //在终端中看不到是因为重定向了标准输出到其他终端
}
int main(){
    //创建子进程
    pid_t pid = fork();
    //退出父进程
    if(pid>0) exit(0);
    //将子进程提升为会话
    if(pid == 0){
        setsid();
        //设置掩码
        umask(022);
        //更改工作目录
        chdir("/");
        //重定向文件描述符
        int fd = open("/dev/null",O_RDWR);
        dup2(fd,STDIN_FILENO);
        dup2(fd,STDOUT_FILENO);
        dup2(fd,STDERR_FILENO);
        //业务逻辑
        //需要捕获sign_alarm信号，因此要注册信号捕获
        struct sigaction act;
        act.sa_flags = 0;
        act.sa_handler = work;
        sigemptyset(&act.sa_mask);
        sigaction(SIGALRM,&act,NULL);

         //每隔几秒执行一个xxx
        //为setitimer构造结构体
        struct itimerval val;
        val.it_value.tv_sec = 2;
        val.it_value.tv_usec = 0;
        val.it_interval.tv_sec = 2;
        val.it_interval.tv_usec = 0;

        //根据结构体创建定时器
        setitimer(ITIMER_REAL,&val,NULL); //根据真实时间定时

        while(1){
            sleep(5);
        }
    }
    return 0;
}