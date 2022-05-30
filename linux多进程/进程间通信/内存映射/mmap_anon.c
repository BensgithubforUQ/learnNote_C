#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

int main(){
    int len = 4096;
    void * ptr = mmap(NULL, len, PROT_WRITE|PROT_READ,MAP_SHARED | MAP_ANONYMOUS,-1,0);//匿名内存映射创建
    if(ptr == MAP_FAILED){
        perror("mmap");
        exit(0);
    }

    //父子进程通信
    pid_t pid = fork();
    if(pid>0){
        strcpy((char *)ptr,"hello , world");//向内存映射中输入字符串信息
        wait(NULL);
    }
    else{
        sleep(1);
        printf("%s\n",(char *)ptr);//子进程打印父进程传递过数据，用匿名内存映射
    }

    munmap(ptr,len);
    return 0;
}