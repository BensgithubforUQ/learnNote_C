#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>

/*
int pthread_detach(pthread_t thread)
功能 分离一个线程，被分离的线程子啊终止的时候，会自动释放资源给系统
不能多次分离，会产生不可预料错误
不能连接一个已经分离的线程，会报错
*/

static int num  = 4;
void *callback(void *arg)
{
    printf("child id :%ld \n", pthread_self());
    int n = 4;
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
    if (ret != 0)
    {
        printf("%s\n", strerror(ret));//获取错误号。
    }
    else
    {
        printf("main thread id: %ld\n", pthread_self());
    }
    for (int i = 100; i > 90; i--)
    {
        //不作处理。
        printf("%d\n",i);
    }
    //设置子线程分离，子线程对应的资源，不需要主线程释放，自动释放
    pthread_detach(tid);
    sleep(1);
    // int *thread_return_value; //一个一级指针，回收子线程退出时的返回值，传入地址
    // int ret1 = pthread_join(tid, (void **)&thread_return_value);//retval
    // //回收成功返回0，如果错误返回错误号
    // if(ret1 == 0) printf("回收 %ld 成功，传出参数为%d\n",tid, (int)*thread_return_value);

    //让主线程退出
    pthread_exit(NULL);
    return 0;
}