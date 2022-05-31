// 线程只是一个进程中的不同执行路径。线程有自己的堆栈和局部变量，
// 但线程没有单独的地址空间，一个线程死掉就等于整个进程死掉，!!!!!
// 所以多进程的程序要比多线程的程序健壮，但在进程切换时，耗费资源较大，效率要差一些。
// 但对于一些要求同时进行并且又要共享某些变量的并发操作，只能用线程，不能用进程。
//内核区和共享库，堆区，bss，data区等是共享的，但是栈区和text区不是共享的（主要由线程id，信号掩码
// 线程特有数据，栈，本地变量和函数调用信息，实时调度策略和优先级等

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


// int pthread_create(pthread_t *__restrict__ __newthread, 
// const pthread_attr_t *__restrict__ __attr, void *(*__start_routine)(void *), void *__restrict__ __arg)
/*
创建子线程
参数
-thread:传出参数，线程创建成功后子线程的线程id邪道该变量中。
-attr：设置线程的属性，一般用NULL
-start_routine 函数指针，子线程需要处理的逻辑代码，回调函数
-arg，给第三个参数使用的参数，传参。
返回值
成功返回0，失败返回错误号。
获取错误号信息用strerror(int errnum);
*/

void* callback(void *arg){ //回调函数
    printf("child thread...\n");
    int num = (*(int *)arg);
    while(1){
        printf("%d\n",num++);
    }
    return NULL;
}

int main(){//用gcc -o -pthread编译
    //创建一个子线程
    pthread_t tid;
    int arg = 10;
    int ret = pthread_create(&tid,NULL,callback,(void*)&arg); //只有这部分是子线程，其他都是主线程
    sleep(2);
    if(ret == 0){
        printf("子线程创建成功\n");
    }
    else if(ret != 0){
        printf("errorL %s\n",strerror(ret));
    }
    for(int i =0;i<5;i++){
        printf("num : %d\n",i);
    }
    return 0;//exit(0);
}