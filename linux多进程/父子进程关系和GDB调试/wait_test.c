#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    /*
    pid_t pid = wait(int *wstatus);
    功能：等任意一个子进程结束，如果任意一个子进程结束，此函数将会回收子进程的PCB
    参数wstatus进程退出时候的状态信息，传入的是一个int类型的地址，传出参数，
    成功返回子进程的pid失败返回-1
    */
   pid_t pid;
   for(int i = 0;i<5;i++){
       pid = fork();
       if(pid == 0){
           break;
       }
   }
   if(pid>0){
       while(1){
           printf("parent process, pid:%d\n",getpid());
           int ret = wait(NULL);//加宏函数可以返回不同的值。
           printf("child killed，pid = %d\n",ret);
           sleep(1);
       }
   }
   else if(pid == 0){
       //子进程
       while(1){
            printf("child process,pid: %d , ppid: %d \n",getpid(),getppid());  
            sleep(1);
       } 
   }
    return 0;
}