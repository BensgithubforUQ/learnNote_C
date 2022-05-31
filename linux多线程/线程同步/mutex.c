#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int main(){
    //互斥量的类型
    pthread_mutex_t mutex;
    //int pthread_mutex_init(pthread_mutex_t *__mutex, const pthread_mutexattr_t *__mutexattr)
    //初始化互斥量
    /*-参数：
    mutex,需要初始化的互斥量变量
    attr互斥量相关的属性，null    
    */
    int ret = pthread_mutex_init(&mutex,NULL);
    //
    int ret1 = pthread_mutex_destroy(&mutex);//释放互斥量资源
    int ret2 = pthread_mutex_lock(&mutex);//加锁，如果一个线程加锁了，其他线程就被阻塞，只能等待
    int ret3 = pthread_mutex_trylock(&mutex);//尝试加锁，如果加锁失败，会返回，不会阻塞
    int ret4 = pthread_mutex_unlock(&mutex);//解锁
    return 0;
}