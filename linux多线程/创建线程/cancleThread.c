#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>

/*
int pthread_cancle(pthread_t thread)
功能 取消线程，让线程终止
必须要到线程执行到取消点的时候，接收到pthread_cancle就取消，线程才能终止。
取消点，系统规定的一些系统调用，粗略的认为是用户区到内核区的切换，这个位置可以是取消点。
*/

static int num = 4;
void *callback(void *arg)
{
    printf("child id :%ld \n", pthread_self());
    int n = 4;
    while(n>0){
        n--;
        printf("child id :%ld \n", pthread_self());
    }
   
    arg = &n;
    pthread_exit(arg);
}

int main()
{
    //任何一个线程都可以回收相关的线程，一般是主线程回收子线程
    //如果线程完成后不被回收，会形成僵尸线程。
    //因此需要回收资源

    pthread_t tid; //需要回收的子线程的id
    void *arg;
    int ret = pthread_create(&tid, NULL, callback, arg);
    for (int i = 100; i > 90; i--)
    {
        //不作处理。
        printf("%d\n", i);
    }
    //取消线程
    pthread_cancel(tid);
    if (ret != 0)
    {
        printf("%s\n", strerror(ret)); //获取错误号。
    }
    else
    {
        printf("main thread id: %ld\n", pthread_self());
    }

    //sleep(1);
    // int *thread_return_value; //一个一级指针，回收子线程退出时的返回值，传入地址
    // int ret1 = pthread_join(tid, (void **)&thread_return_value);//retval
    // //回收成功返回0，如果错误返回错误号
    // if(ret1 == 0) printf("回收 %ld 成功，传出参数为%d\n",tid, (int)*thread_return_value);

    //让主线程退出
    pthread_exit(NULL);
    return 0;
}