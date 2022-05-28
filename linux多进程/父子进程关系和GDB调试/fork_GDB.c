 #include <sys/types.h>
 #include <unistd.h>
 #include <stdio.h>

int main(){
    /*
    set detach-on-fork off //挂起其他进程
        info inferiors //查看进程信息
        inferiors n //切换到n进程
    set follow-fork-mode off //多进程调试
    */
    int num = 0;
    pid_t pid = fork();
    if(pid>0){
        num = num + 10;//不可用变量做进程通信
        printf("parent -- pid: %d, ppid: %d，num: %d \n",getpid(),getppid(),num);
    }
    else if(pid == 0){
        pid_t s_pid = fork();
        if(s_pid > 0){
            num = num + 100;
            printf("son -- pid: %d, ppid: %d，num: %d \n",getpid(),getppid(),num);
        }
        else if(s_pid == 0){
            num = num + 1000;
            printf("son's son -- pid: %d, ppid: %d，num: %d \n",getpid(),getppid(),num);
        }
    }
    for(int i = 0;i<5;i++){
        printf("pid: %d, ppid: %d，num: %d \n",getpid(),getppid(),++num);
        sleep(1);
    }
    return 0; 
}