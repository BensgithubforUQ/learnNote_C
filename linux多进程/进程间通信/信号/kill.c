#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

int main()
{
    // int kill(pid_t pid, int sig);给任何进程或者进程组发送任何信号
    // pid进程id
    /*
        >0 指定进程
        =0 当前进程组
        =-1 每个有权限接受这个信号的进程
        <-1 这个pid=某个进程组id取反（-12345）
    */
    // sig，需要发送的信号宏值。
    /*
    int raise(int sig)
    发送给信号给当前进程
    */
    /*
    void abort(void);
    发送sigabort给当前进程，杀死进程
    */
    pid_t pid = fork();
    if (pid == 0)
    {
        int i = 0;
        for (i = 0; i < 5; i++)
        {
            sleep(1);
            printf("child process\n");
        }
    }

    if (pid > 0)
    {
        sleep(2);
        printf("parent process\n");

        printf("kill child process\n");

        kill(pid, 2); //怎么我的好像不认sigint啊。。。

    }
    return 0;
}