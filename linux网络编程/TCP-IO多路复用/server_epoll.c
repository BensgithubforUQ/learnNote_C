// TCP通信的服务器端 - epoll  比select优秀
/*
select具有服务器端接入少的时候具有高性能
并且windows下实现相同，因此具有兼容性

但是缺点是
1.每次调用select函数都需要想操作系统传递监视对象的信息（监视文件描述符是从用户区传递到内核区的）
2.并且每次都要遍历文件描述符集，非常浪费。

epoll流程
先创建epoll例程
epoll_create
然后注册
epoll_ctl
其中ctl中需要用到epoll_event类型的结构体
该结构体类似select中的fd_set,记录发生事件的文件描述符的信息
其中events成员保存了事件类型
fd成员保存的是事件描述符。
ctl中会指定操作类型，del就是删除，add就是增加，mod就是改变
之后就是epoll_wait,
调用之后，返回发生事件的文件描述符，并且将其集合保存在第二个参数里面，第四个参数设置的是等待时间，如果-1，就阻塞。
epoll默认是条件触发的（水平触发），但是可以改成边缘触发。
所谓条件触发，只要输入缓冲中还有数据（没读完），就以事件方式再次注册
所谓边缘触发，就是输入缓冲收到数据的时候注册一次()
*/



#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/epoll.h>

#define EPOLL_SIZE 50
#define BUF_SIZE 100
int main()
{
    //创建socket（监听）
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    // domain,协议,流式协议
    if (listen_fd == -1)
    {
        perror("socket");
        exit(0);
    }
    //绑定（ip和port）
    struct sockaddr_in sockAddr;
    sockAddr.sin_family = AF_INET;
    int ip_addr = inet_pton(AF_INET, "192.168.19.128", &sockAddr.sin_addr.s_addr);
    // sockAddr.sin_addr.s_addr = 0;//0.0.0.0,可以偷懒这么写
    sockAddr.sin_port = htons(9999);
    int ret_bind = bind(listen_fd, (struct sockaddr *)&sockAddr, sizeof(sockAddr));
    if (ret_bind == -1)
    {
        perror("bind");
        exit(0);
    }
    //监听
    int ret_listen = listen(listen_fd, 8);
    if (ret_listen == -1)
    {
        perror("listen");
        exit(0);
    }

    //定义epoll结构体和相关参数
    struct epoll_event *ep_events; // epoll事例
    struct epoll_event event;
    int epfd, event_cnt;
    // epoll fd
    epfd = epoll_create(EPOLL_SIZE);                             //创建EPOLL_SIZE大小的文件描述符保存空间
    ep_events = malloc(sizeof(struct epoll_event) * EPOLL_SIZE); //在堆区分配EPOLL_SIZE大小的空间

    event.events = EPOLLIN; //初始化event，为需要读取数据的情况
    event.data.fd = listen_fd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, listen_fd, &event); //把listen_fd注册到epfd中

    //获取客户端数据
    while (1)
    {
        //记录有"反应"的文件描述符的个数
        event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);
        // epfd 表示事件发生监视范围的epoll例程的文件描述符
        // event 保存了发生事件的文件描述符集合的结构体地址
        // maxevent第二个参数的最大事件数
        //等待时间，设置为-1就阻塞
        if (event_cnt == -1)
        {
            puts("event_wait error");
            break;
        }

        //如果文件描述符有变化
        for (int i = 0; i < event_cnt; i++)
        {
            if (ep_events[i].data.fd == listen_fd) //如果是监视套接字
            {
                //建立新的连接
                //通信
                //接受客户端连接
                struct sockaddr_in clientAddr;
                int len = sizeof(clientAddr);
                int ret_acc = accept(listen_fd, (struct sockaddr *)&clientAddr, &len);
                //如果成功，返回的是一个fd，是客户端的数据
                event.events = EPOLLIN; 
                event.data.fd = ret_acc;
                epoll_ctl(epfd, EPOLL_CTL_ADD, ret_acc, &event); //ret_acc注册
                printf("new connected clinet: %d \n", ret_acc);
            }
            else
            {
                //如果不等于监听套接字，则是已存在的连接
                char client_buf[1024] = {0};
                int ret_read = read(ep_events[i].data.fd, client_buf, sizeof(client_buf));
                if (ret_read == -1)
                {
                    perror("read");
                    exit(0);
                }
                else if (ret_read > 0)
                { //表示读到了数据
                    printf("received client data： %s\n", client_buf);
                    write(ep_events[i].data.fd, client_buf, ret_read); // echo回声
                }
                else if (ret_read == 0)
                {
                    //客户端断开连接
                    epoll_ctl(epfd,EPOLL_CTL_DEL,ep_events[i].data.fd,NULL);//从例程中删除
                    close(ep_events[i].data.fd);//释放该文件描述符
                    printf("client closed connection...");
                }
            }
        }
    }

    //关闭文件描述符
    // close(ret_acc);
    close(epfd);
    close(listen_fd);

    return 0;
}