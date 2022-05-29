#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

    //    pid_t wait(int *wstatus);

    //    pid_t waitpid(pid_t pid, int *wstatus, int options);
    /*
    pid>0,某个子进程的pid
    pid==0，回收当前进程组的所有子进程
    pid==-1,回收所有的子进程，相当于wait();,包括送给别的进程组的子进程。 （最常用）
    pid < -1，回收某个进程组的组id的绝对值，回收指定进程组的子进程

    -options设置阻塞或者非阻塞
    0阻塞
    WNOHANG非阻塞
    返回值，>0 子进程id
    =0 表示还有子进程
    =-1错误，或者没有子进程
        */
int main(){
pid_t pid;
   for(int i = 0;i<5;i++){
       pid = fork();
       if(pid == 0){
           break;
       }
   }
   if(pid>0){
       while(1){
                      
           sleep(1);
           printf("parent process, pid:%d\n",getpid());
           int ret = waitpid(-1,NULL,WNOHANG);//加宏函数可以返回不同的值。不挂起的话，可以让父进程有时间片处理其他的事情
           if(ret == -1) break;
           if(ret == 0){
               continue;
           }
           if(ret>0) printf("child killed，pid = %d\n",ret);

       }
   }
   else if(pid == 0){
       srand((unsigned)time(NULL));
       //子进程
       while(1){
            printf("child process,pid: %d , ppid: %d \n",getpid(),getppid());  
            int r = rand()%10;
            if(r>10) exit(0);
            sleep(1);
       } 
   }
    return 0;
}