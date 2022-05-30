 #include <unistd.h>
 #include <sys/types.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

int main(){
    int pipefd[2];
    int ret = pipe(pipefd);
    //需要在fork之前创建管道，因为是在内核区的缓冲区。
    //创建一个匿名管道，管道的数据结构是一个环形的队列。
    //匿名管道还是内核区里面的一个缓冲区。
    //int pipefd[2]是一个传出参数
    //pipefd[0] 对应管道的读端
    //pipefd[1] 对应管道的写端
    if(ret == -1){
        perror("pipe");
        exit(0);
    }
    //子进程发送数据给父进程，父进程属性举出
    pid_t pid = fork();
    if(pid>0){
        printf("父进程\n");
        char buf[1024] = {0};
        int len = read(pipefd[0],buf,sizeof(buf));
        printf("内容是：%s\n",buf);
    }
    else if(pid == 0){
        sleep(10); //管道默认是阻塞的，如果管道中没有数据，那么读操作那一侧的进程就会被阻塞
        printf("子进程\n");
        char * str = "hello world, this is a info convert in the pipe between parent and child.\n";
        write(pipefd[1],str,strlen(str));
        long size = fpathconf(pipefd[0], _PC_PIPE_BUF);
        printf("pipe size : %ld\n",size);
    }
}