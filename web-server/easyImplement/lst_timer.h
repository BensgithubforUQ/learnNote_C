#ifndef LST_TIMER
#define LST_TIMER

#include <signal.h>
#include <sys/epoll.h>
class util_timer;//提前定义，定时器类
struct clent_data //连接资源结构体成员需要用到定时器类
{
    /* data */
    sockaddr_in address; //客户端socket地址
    int sockfd; //socket文件描述符
    //定时器
    util_timer *timer;
};


//定时器类
class util_timer{
public:
    util_timer():prev(NULL),next(NULL){};
public:
    //超时
    time_t expire;
    //回调函数 定时事件，具体的，从内核事件表删除事件，关闭文件描述符，释放连接资源。
    void (*cb_func)(client_data*);
public:
    //连接资源
    client_data * user_data;
    //向前定时器
    util_timer* prev;
    //向后定时器
    util_timer* next;
};

void cb_func(client_data *user_data){
    //
    epoll_ctl
}
#endif