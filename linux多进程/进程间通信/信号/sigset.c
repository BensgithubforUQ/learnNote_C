#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

// //        int sigemptyset(sigset_t *set);
// 清空信号集重点数据，将信号集中所有的标志位设为0
// 参数set，传出参数，需要操作的信号集
// 返回值，成功返回0，否则返回-1
// //        int sigfillset(sigset_t *set);
// 将信号集中所有的标志位设置为1
// //        int sigaddset(sigset_t *set, int signum);
// 设置某一个标志位为1，阻塞这个信号
// //        int sigdelset(sigset_t *set, int signum);
// 设置某一个标志位为0，表示解除阻塞
// //        int sigismember(const sigset_t *set, int signum);
// 判断某个信号是否是阻塞的。
//返回值1，阻塞，返回0，不阻塞，返回-1，错误。

// int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
/*
    -how 如何处理内核阻塞信号机
    sig_block,将用户设置的阻塞信号集添加到内核中，内核中原来的数据不变，只添加阻塞，不添加不阻塞。
    sig_unblock，根据用户设置的阻塞信号集，清楚内核中的阻塞状态的。
    sig_setmask,用用户自定义的信号集覆盖内核中的信号集
    old set保存的是之前内核中的阻塞信号集

*/

int main()
{
    //创建一个信号集

    sigset_t set;
    sigemptyset(&set); //没有初始化的信号集里面可能有的标志位有值，用sigemptyset清空
    int ret = sigismember(&set, SIGINT);
    if (ret == 0)
    {
        printf("不阻塞\n");
    }
    if (ret == 1)
    {
        printf("阻塞\n");
    }
    sigaddset(&set, SIGINT);
    ret = sigismember(&set, SIGINT);
    if (ret == 0)
    {
        printf("不阻塞\n");
    }
    if (ret == 1)
    {
        printf("阻塞\n");
    }
    sigdelset(&set, SIGINT);
    ret = sigismember(&set, SIGINT);
    if (ret == 0)
    {
        printf("不阻塞\n");
    }
    if (ret == 1)
    {
        printf("阻塞\n");
    }

    // sigprocmask
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);
    //修改内核中的阻塞信号集
    sigprocmask(SIG_BLOCK, &set, NULL);
    int num = 0;
    while (1)
    {
        sleep(1);
        num ++;
        /* code */
        sig_t set1;
        sigemptyset(&set1);
        sigpending(&set1);
        for (int i = 0; i <= 32; i++){
            if (sigismember(&set1, i) == 1)
            {
                printf("1");
            }
            else{
                printf("0");
            }
        }
        printf("\n");
        if(num == 10){
            //解除阻塞
            sigprocmask(SIG_UNBLOCK,&set1,NULL);
        }
    }

    return 0;
}