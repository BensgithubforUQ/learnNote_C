#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    /*
    int execl(const char *path, const char *arg, (char  *) NULL );
    用找到的文件，替换当前进程的用户区（栈区，堆区，bss区，数据区，代码区等）
    类似移花接木。
    */
   pid_t pid = fork();
   if(pid>0){
       printf("父进程\n");
   }
   else if(pid == 0){
       printf("子进程\n");
       pid_t s_pid = fork();
       if(s_pid > 0){
           execl("app","app", NULL); //从路径找，找到就运行
           printf("测试是否能打印1？");
       }
       else if(s_pid == 0){
           execlp("ps","ps","aux",NULL); //从环境变量中查找文件，找到就运行
           printf("测试是否能打印2？");
       }
       
   }

    printf("进程pid：%d，进程ppid: %d \n",getpid(),getppid());
    return 0;
}