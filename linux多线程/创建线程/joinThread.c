#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>


static int num  = 4;
void *callback(void *arg)
{
    printf("child id :%ld \n", pthread_self());
    // int * num = (int *)malloc(sizeof(4));
    // *num = 4;
    // pthread_self 返回当前线程的id。
    pthread_exit((void *)&num);
}

int main()
{
    //任何一个线程都可以回收相关的线程，一般是主线程回收子线程
    //如果线程完成后不被回收，会形成僵尸线程。
    //因此需要回收资源

    pthread_t tid; //需要回收的子线程的id
    int ret = pthread_create(&tid, NULL, callback, NULL);
    if (ret != 0)
    {
        printf("%s\n", strerror(ret));
    }
    else
    {
        printf("main thread id: %ld\n", pthread_self());
    }
    for (int i = 100; i > 0; i++)
    {
        //不作处理。
    }
    //让主线程退出
    sleep(1);
    int *thread_return_value; //一个一级指针，回收子线程退出时的返回值，传入地址
    int ret1 = pthread_join(tid, (void **)&thread_return_value);//retval
    //回收成功返回0，如果错误返回错误号
    if(ret1 == 0) printf("回收 %ld 成功，传出参数为%d\n",tid, *thread_return_value);
    pthread_exit(NULL);
    return 0;
}