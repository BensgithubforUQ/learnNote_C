#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *callback(void *arg){
    return NULL;
}

int main(){
    /*
     int pthread_attr_init(pthread_attr_t *attr);
     -初始化线程属性变量
     int pthread_attr_destroy(pthread_attr_t *attr);
     -释放线程属性的资源
     int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
     -设置线程分离的状态属性
     int pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate);
     -获取线程分离的状态属性
    */

    //创建一个线程属性变量
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    //设置属性
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

    
    pthread_t tid;

    int ret = pthread_create(&tid,&attr,callback,NULL);

    if(ret != 0){
        printf("error1: %s\n",strerror(ret));
    }
    //获取线程的栈的大小
    int  *size;
    pthread_attr_getstacksize(&attr,&size);
    printf("线程的栈的大小为：%ld\n",size);
    //输出主线程和子线程的id
    printf("tid: %ld, main thread id: %ld\n",tid, pthread_self());
    //释放线程属性资源
    pthread_attr_destroy(&attr);
    pthread_exit(NULL);

    return 0;
}