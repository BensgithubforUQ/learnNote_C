#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include "locker.h"
#include "threadpool.h"
#include "http_conn.h"

#define MAX_FD 65536           // 最大的文件描述符个数
#define MAX_EVENT_NUMBER 10000 // 监听的最大的事件数量

//向epoll例程中添加文件描述符
extern void addfd(int epollfd, int fd, bool one_shot);
//从epoll例程中删除文件描述符
extern void removefd(int epollfd, int fd);

//设置信号捕捉
void addsig(int sig, void(handler)(int))
{                                            // void( handler )(int)是函数指针，是sa被捕捉到之后执行的处理函数
    struct sigaction sa;                     // sigaction结构体
    memset(&sa, '\0', sizeof(sa));           //初始化
    sa.sa_handler = handler;                 //处理函数
    sigfillset(&sa.sa_mask);                 //临时阻塞信号集，信号捕捉函数执行过程中，临时阻塞某些信号
    assert(sigaction(sig, &sa, NULL) != -1); //断言函数，用于在调试过程中捕捉程序的错误。
}

int main(int argc, char *argv[])
{

    if (argc <= 1)
    {
        printf("usage: %s port_number\n", basename(argv[0]));
        return 1;
    }

    int port = atoi(argv[1]);
    addsig(SIGPIPE, SIG_IGN);//如果捕捉到sigpipe，忽略
    //当一个进程向某个已收到RST的套接字执行写操作时，内核向该进程发送SIGPIPE信号。
    //当服务器close一个连接时，若client端接着发数据。
    //根据TCP协议的规定，会收到一个RST响应，client再往这个服务器发送数据时，
    //系统会发出一个SIGPIPE信号给进程，告诉进程这个连接已经断开了，不要再写了。
    //根据信号的默认处理规则SIGPIPE信号的默认执行动作是terminate(终止、退出),
    //所以client会退出。若不想客户端退出可以把SIGPIPE设为SIG_IGN


    threadpool<http_conn> *pool = NULL; //定义线程池并且，初始化
    try
    {
        pool = new threadpool<http_conn>; //如果异常
    }
    catch (...)
    {
        return 1; //返回1
    }

    http_conn *users = new http_conn[MAX_FD]; //创建一个数组用于存放(用户之间连接的信息)

    int listenfd = socket(PF_INET, SOCK_STREAM, 0); //监听套接字

    int ret = 0;                          //一些返回值
    struct sockaddr_in address;           //监听套接字的结构体地址
    address.sin_addr.s_addr = INADDR_ANY; //本机所有IP
    address.sin_family = AF_INET;         // IPV4协议
    address.sin_port = htons(port);       //把从内存中读出来的port host -> network & short

    // 端口复用
    int reuse = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    // 写Socket程序的时候经常会遇到这个问题：如果自己的程序不小心崩溃了，
    // 重新启动程序的时候往往会在bind调用上失败，错误原因为Address Already In Use，往往要等待两分钟才能再次绑定。
    // 原因是假如端口被socket使用过，并且利用socket.close()来关闭连接，但此时端口还没有释放，(TIME_WAIT)
    // 要经过一个TIME_WAIT的过程之后才能使用。为了实现端口的马上复用，可以选择setsockopt()函数来达到目的。
    ret = bind(listenfd, (struct sockaddr *)&address, sizeof(address)); //绑定
    ret = listen(listenfd, 5);
    // 5： backlog ：内核会在自己的进程空间里维护一个队列以跟踪这些完成的连接但服务器进程还没有接手处理或正在进行的连接，
    //这样的一个队列内核不+可能让其任意大，所以必须有一个大小的上限。

    // IO复用 创建epoll对象，和事件数组，添加
    // 使用一个线程来检查多个文件描述符的就绪状态(主线程)
    // 如果有一个文件描述符就绪，则返回
    // 否则阻塞直到超时
    // 得到就绪状态后进行真正的操作可以在同一个线程里执行，也可以启动线程执行（线程池）
    // 本质上是没有阻塞的
    epoll_event events[MAX_EVENT_NUMBER]; //epoll
    int epollfd = epoll_create(5); //文件描述符保存空间 epoll例程
    // 添加到epoll对象中
    addfd(epollfd, listenfd, false); //将监听套接字注册到epoll例程中

    //将上述epollfd赋值给http类对象的m_epollfd属性
    http_conn::m_epollfd = epollfd; 

    while (true) //循环执行
    {

        int number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1); //返回触发事件的文件描述符的集合的数量
        //events中保存触发事件的文件描述符的集合
        if ((number < 0) && (errno != EINTR))
        {
            printf("epoll failure\n");
            break;
        }
        for (int i = 0; i < number; i++)
        {
            int sockfd = events[i].data.fd;//取出集合中的文件描述符

            if (sockfd == listenfd) //如果是监听套接字，那说明有新的连接
            {
                struct sockaddr_in client_address; 
                socklen_t client_addrlength = sizeof(client_address);
                //接受新的连接 
                //LT水平触发
                int connfd = accept(listenfd, (struct sockaddr *)&client_address, &client_addrlength);
                if (connfd < 0) //没有连接
                {
                    printf("errno is: %d\n", errno);
                    continue;
                }
                if (http_conn::m_user_count >= MAX_FD) //超出上限
                {
                    close(connfd);
                    continue;
                }
                users[connfd].init(connfd, client_address); //正常连接，初始化新接受的连接
            }
            else if (events[i].events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR))
            {
                // events->data.fd; 文件描述符
                // events->events; 文件描述符的事件类型
                // EPOLLRDHUP 断开连接或者半关闭
                // EPOLLHUP 当socket的一端认为对方发来了一个不存在的4元组请求的时候,会回复一个RST响应
                // EPOLLERR 发生错误
                users[sockfd].close_conn(); //关闭连接
            }
            else if (events[i].events & EPOLLIN)//读取数据
            {
                if (users[sockfd].read())
                {
                    pool->append(users + sockfd);//如果检测到读事件，将这个事件放到请求队列
                    // 浏览器端发出http连接请求，服务器端主线程创建http对象接收请求并将所有数据读入对应buffer，
                    // 将该对象插入任务队列后，工作线程从任务队列中取出一个任务进行处理。
                }
                else
                {
                    users[sockfd].close_conn();
                }
            }
            else if (events[i].events & EPOLLOUT)//输出缓存为空，立即发送数据
            {

                if (!users[sockfd].write())
                {
                    users[sockfd].close_conn();
                }
            }
        }
    }

    close(epollfd);
    close(listenfd);
    delete[] users;
    delete pool;
    return 0;
}