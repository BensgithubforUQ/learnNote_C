/*
生产者消费者模型非信号量版本,问题展示
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
//用链表当容器，不考虑存满，可以无限储存。
struct Product
{
    int num;
    struct Product *next;
    /* data */
};
//造锁
pthread_mutex_t mutex;
//创建条件变量
sem_t pro, cus;
struct Product *head = NULL;
// 进化版的互斥锁（1 --> N）

// 由于互斥锁的粒度比较大，如果我们希望在多个线程间对某一对象的部分数据进行共享，使用互斥锁是没有办法实现的，
// 只能将整个数据对象锁住。这样虽然达到了多线程操作共享数据时保证数据正确性的目的，却无形中导致线程的并发性下降
// 线程从并行执行，变成了串行执行。与直接使用单进程无异。

// 信号量，是相对折中的一种处理方式，既能保证同步，数据不混乱，又能提高线程并发。

void *produce(void *arg)
{
    while (1)
    {
        sem_wait(&pro);             //调用一次，pro的值-1，默认一开始为8
        pthread_mutex_lock(&mutex); //锁住
        struct Product *newProduct = (struct Product *)malloc(sizeof(struct Product));
        newProduct->next = head;
        head = newProduct;
        newProduct->num = rand() % 100;
        printf("add node, num :%d, tid: %ld\n", newProduct->num, pthread_self());
        pthread_mutex_unlock(&mutex); //解锁
        sem_post(&cus);//cus++
        usleep(1000);
    }
    return NULL;
}

void *consum(void *arg)
{
    while (1)
    {
        sem_wait(&cus);//如果不为0，就可以放过去了，因此不需要判断是否为空
        pthread_mutex_lock(&mutex); //锁住
        usleep(1000);
        struct Product *temp = head; //保存头结点的指针
        //链表不为空
        head = head->next; //往后移
        printf("del node, num :%d, tid: %ld\n", temp->num, pthread_self());
        free(temp);
        pthread_mutex_unlock(&mutex); //解锁
        sem_post(&pro);//给生产者加空位，pro++
        usleep(1000);
    }
    return NULL;
}

int main()
{
    pthread_mutex_init(&mutex, NULL); //初始化锁
    sem_init(&pro, 0, 8);             //初始化信号量
    sem_init(&cus, 0, 0);
    //创建五个生产者线程和五个消费者线程
    pthread_t ptid[5], ctid[5];
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&ptid[i], NULL, produce, NULL);
        pthread_create(&ctid[i], NULL, consum, NULL);
    }

    //线程分离
    for (int i = 0; i < 5; i++)
    {
        pthread_join(&ctid[i], NULL);
        pthread_join(&ptid[i], NULL);
    }
    while (1)
    {
    }

    pthread_mutex_destroy(&mutex); //销毁锁
    pthread_exit(NULL);
    return 0;
}