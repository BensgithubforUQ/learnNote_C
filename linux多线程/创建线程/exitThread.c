#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void* callback(void *arg){
    printf("child id :%ld \n",pthread_self());
    //pthread_self 返回当前线程的id。
    return NULL;
}

int main(){
    pthread_t tid;
    int ret = pthread_create(&tid,NULL,callback,NULL);
    if(ret != 0){
        printf("%s\n",strerror(ret));

    }
    else{
        printf("main thread id: %ld\n",pthread_self());
    }
    for(int i = 100;i>0;i++){
        //不作处理。
    }
    //让主线程退出
    pthread_exit(NULL);
    //retval需要传入一个指针，由pthread_join产生，可以置为null。
    printf("main thread exits");
    return 0;
}