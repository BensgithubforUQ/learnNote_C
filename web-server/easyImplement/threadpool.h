#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <list>
#include <cstdio>
#include <exception>
#include <pthread.h>
#include "locker.h"

// 线程池类，将它定义为模板类是为了代码复用，模板参数T是任务类
template <typename T>
class threadpool
{
public:
    /*thread_number是线程池中线程的数量，max_requests是请求队列中最多允许的、等待处理的请求的数量*/
    threadpool(int thread_number = 8, int max_requests = 10000);
    ~threadpool();
    bool append(T *request);

private:
    /*工作线程运行的函数，它不断从工作队列中取出任务并执行之*/
    static void *worker(void *arg);
    void run();

private:
    // 线程的数量
    int m_thread_number;
    // 描述线程池的数组，大小为m_thread_number
    pthread_t *m_threads;
    // 请求队列中最多允许的、等待处理的请求的数量
    int m_max_requests;
    // 请求队列
    std::list<T *> m_workqueue;
    // 保护请求队列的互斥锁
    locker m_queuelocker;
    // 是否有任务需要处理
    sem m_queuestat;
    // 是否结束线程
    bool m_stop;
};

template <typename T>
threadpool<T>::threadpool(int thread_number, int max_requests) : m_thread_number(thread_number), m_max_requests(max_requests),
                                                                 m_stop(false), m_threads(NULL)
{

    if ((thread_number <= 0) || (max_requests <= 0))
    {
        throw std::exception();
    }

    m_threads = new pthread_t[m_thread_number];
    if (!m_threads)
    {
        throw std::exception();
    }

    // 创建thread_number 个线程，并将他们设置为脱离线程。
    for (int i = 0; i < thread_number; ++i)
    {
        printf("create the %dth thread\n", i);
        if (pthread_create(m_threads + i, NULL, worker, this) != 0)
        {
            delete[] m_threads;
            throw std::exception();
        }

        if (pthread_detach(m_threads[i]))
        {
            delete[] m_threads;
            throw std::exception();
        }
    }
}

template <typename T>
threadpool<T>::~threadpool()
{
    delete[] m_threads;
    m_stop = true;
}

template <typename T>
bool threadpool<T>::append(T *request)
{
    //操作工作队列时一定要加锁，因为它被所有线程共享。
    //通过list容器创建请求队列，向队列中添加时，通过互斥锁保证线程安全，
    
    m_queuelocker.lock();
    if (m_workqueue.size() > m_max_requests)
    {
        m_queuelocker.unlock();
        return false;
    }
    m_workqueue.push_back(request);
    m_queuelocker.unlock();
    m_queuestat.post();
    //添加完成后通过信号量提醒有任务要处理，最后注意线程同步。
    return true;
}

template <typename T>
void *threadpool<T>::worker(void *arg) //线程处理函数，内部访问私有成员函数run，完成线程处理要求。
{
    // int pthread_create (pthread_t *thread_tid,          //返回新生成的线程的id
    //                 const pthread_attr_t *attr,         //指向线程属性的指针,通常设置为NULL
    //                 void * (*start_routine) (void *),   //处理线程函数的地址
    //                 void *arg);                         //start_routine()中的参数
    // pthread_create(m_threads + i, NULL, worker, this)
    // 三个参数，为函数指针，指向处理线程函数的地址。
    // 该函数，要求为静态函数。如果处理线程函数为类成员函数时，需要将其设置为静态成员函数。
    // this指针的锅
    // pthread_create的函数原型中第三个参数的类型为函数指针，指向的线程处理函数参数类型为(void *),
    // 若线程函数为类成员函数，则this指针会作为默认的参数被传进函数中，从而和线程函数参数(void*)不能匹配，不能通过编译。
    threadpool *pool = (threadpool *)arg;
    pool->run();
    return pool;
}

template <typename T>
void threadpool<T>::run() //线程运行函数，主要实现，工作线程从请求队列中取出某个任务进行处理，注意线程同步。
{
    while (!m_stop)
    {
        //信号量等待
        m_queuestat.wait();
        //被唤醒，互斥锁
        m_queuelocker.lock();
        if (m_workqueue.empty())
        {
            m_queuelocker.unlock();
            continue;
        }
        T *request = m_workqueue.front();
        m_workqueue.pop_front();
        //解锁
        m_queuelocker.unlock();
        if (!request)
        {
            continue;
        }
        request->process();
    }
}

#endif
