//线程同步
//多线程实现卖票案例
/*
三个窗口，并发的去卖一百张票
一共一百张票
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>



static int tickets = 100;
//创建互斥量
pthread_mutex_t mutex;
//三个线程是并发执行的，回去抢用cpu资源
//线程不安全，需要线程同步
void *selling (void *arg){
    //m卖票
    //临界区是指访问某一共享资源的代码片段，并且这段代码应该是原子操作，同时访问同一共享资源的其他进程不能中断该片段的执行
    //线程同步，当有一个线程在对内存进行操作的时候，其他线程都不可以对这个内存地址进行操作
    //知道该线程完成操作，其他线程才能对该内存地址进行操作。
    //其他线程处于等待状态。
    //线程同步会带来效率问题，但是能保护线程安全。
    
    
    while(1){//应该设置为原子操作
        //加锁
        pthread_mutex_lock(&mutex);
        if(tickets>0){
            //pthread_mutex_lock(&mutex);死锁情况一，重复加相同的锁
            usleep(3000);
            printf("%ld 正在卖 第 %d 张门票 \n",pthread_self(),tickets);
            tickets--;
            pthread_mutex_unlock(&mutex);
            //pthread_mutex_unlock(&mutex);死锁情况二，忘记释放锁。
            
            usleep(3000);
        }
        else{
            //解锁
            pthread_mutex_unlock(&mutex);
            break;
        }
    }
    return NULL;
}

// void* work1(void* arg){//死锁情况三，多线程多资源多锁。
//     pthread_mutex_lock(&mutex1);
//     sleep(1);
//     pthread_mutex_lock(&mutex2);
//     printf("1");
//     pthread_mutex_lunock(&mutex2);
//     pthread_mutex_unlock(&mutex1);
// }

// void* work2(void* arg){//死锁情况三，多线程多资源多锁。
//     pthread_mutex_lock(&mutex2);
//     sleep(1);
//     pthread_mutex_lock(&mutex1);
//     printf("1");
//     pthread_mutex_lunock(&mutex1);
//     pthread_mutex_unlock(&mutex2);
// }

int main(){

    //初始化互斥量
    pthread_mutex_init(&mutex,NULL);
    //创建三个子线程，多个子线程一般做同样的事情。
    pthread_t tid1,tid2,tid3;
    pthread_create(&tid1,NULL,selling,NULL);
    pthread_create(&tid2,NULL,selling,NULL);
    pthread_create(&tid2,NULL,selling,NULL);

    //回收子线程的资源阻塞
    
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_join(tid2,NULL);
    //设置线程分离
    // pthread_detach(tid1);
    // pthread_detach(tid2);
    // pthread_detach(tid3);

    pthread_mutex_destroy(&mutex);//释放互斥量资源
    pthread_exit(NULL);//退出主线程

    return 0;
}