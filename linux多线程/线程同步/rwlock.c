#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

static int num = 1;
pthread_rwlock_t mutex;
void * writeNum(void * arg){
    while(1){
        pthread_rwlock_wrlock(&mutex);
        num++;
        printf("write ++,tid : %ld, num: %d \n",pthread_self(),num);
        pthread_rwlock_unlock(&mutex);
        usleep(1000);
    }
    return NULL;
}

void * readNum(void * arg){
     while(1){
        pthread_rwlock_rdlock(&mutex);
        printf("read ==,tid : %ld, num: %d \n",pthread_self(),num);
        pthread_rwlock_unlock(&mutex);
        usleep(1000);
    }
    return NULL;
}

int main(){

    //读写锁
    pthread_rwlock_init(&mutex,NULL);
    //3个写线程，5个读线程
    pthread_t wtids[3],rtids[5];
    //创建线程
    for(int i = 0;i<3;i++){
        pthread_create(&wtids[i],NULL,writeNum,NULL);
    }
    for(int i = 0;i<5;i++){
        pthread_create(&rtids[i],NULL,readNum,NULL);
    }

    //设置线程分离
    for(int i = 0;i<3;i++){
        pthread_join(&wtids[i],NULL);
    }
    for(int i = 0;i<5;i++){
        pthread_join(&rtids[i],NULL);
    }

    pthread_exit(NULL);
    pthread_rwlock_destroy(&mutex);
    return 0;
}