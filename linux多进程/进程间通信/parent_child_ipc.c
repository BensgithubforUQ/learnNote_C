 #include <unistd.h>
 #include <sys/types.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <wait.h>

 /*
 实现ps aux | grep xxx父子进程之间的通信

 子进程ps aux，子进程结束后数据发送给父进程
 父进程 获取数据，过滤

 pipe（）
 execlp（）
 子进程还要将标准输出stdout_fileno重新定向到管道的写端。dup2

 */

int main(){
    int fd[2];
    int ret = pipe(fd);
    if(ret == -1){
        perror("pipe");
        exit(0);
    }
    //子进程
    pid_t pid = fork();
    if(pid > 0){
        //father
        close(fd[1]);
        char buf[1024] = {0};
        int len = 0;
        do{
            len = read(fd[0],buf,sizeof(buf)-1);
            printf("%s",buf);
        } while (len > 0);
        memset(buf,0,1024);//回收buf
        wait(NULL); //回收子进程资源
        
    }
    else if(pid == 0){
        //child
        //文件描述符重定向，让子进程把ps aux的输出定向到pipe的写端
        close(fd[0]);
        //因为子进程只负责写，为了防止又读又写，关闭读端
        dup2(fd[1],STDIN_FILENO);
        //执行ps aux
        int  exc = execlp("ps","ps","aux",NULL);
        if(exc == -1){
            perror("execlp");
            exit(0);
        }
    }
    else{
        perror("fork");
        exit(0);
    }
    return 0;
}