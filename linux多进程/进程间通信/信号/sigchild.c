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
#include <wait.h>

void myFun(int a){
    printf("捕捉到信号sigchild：%d\n",a);
    //回收子进程pcb资源
    while(1){
        int ret = waitpid(-1,NULL,WNOHANG);
        if(ret > 0){
            printf("捕捉到child的sigchild信号：%d\n",ret);
        }
        else if(ret == 0){
            break;
        }else if(ret == -1){
            break;
        }
    }
}

int main(){
    //子进程结束，子进程暂停，子进程继续运行，都会给父进程发送sigchild信号，父进程默认ignore这些信号
    //可以用sigchild来解决僵尸问题
    pid_t pid;
     sigset_t set;
    sigemptyset(&set); //没有初始化的信号集里面可能有的标志位有值，用sigemptyset清空
    sigaddset(&set,SIGCHLD);
    sigprocmask(SIG_BLOCK,&set,NULL);
    //为了防止又子进程在父进程注册捕获信号之前就结束，提前阻塞sigchild
    for(int i =0;i<10;i++){
        pid = fork();
        if(pid == 0){
            break;
        }
    }
    if(pid>0){
        //父进程
        //捕捉子进程发出的sigchild
        struct sigaction act;
        act.sa_flags = 0;
        act.sa_handler = myFun;
        sigemptyset(&act.sa_mask); //这个信号集没有排队机制，如果有没有处理的存在，这时又产生新的，就无法记录。
        sigaction(SIGCHLD,&act,NULL);

        //在捕获一次之后，就解除sigprocmask设置的阻塞
        sigprocmask(SIG_UNBLOCK,&set,NULL);
        while(1){
            printf("parent process, pid: %d\n",getpid());
            
            sleep(2);
        }
    }

    if(pid == 0){
        printf("child process ,pid: %d, ppid: %d\n",getpid(),getppid());
    }
    return 0;
}