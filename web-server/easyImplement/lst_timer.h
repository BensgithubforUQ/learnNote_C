#ifndef LST_TIMER
#define LST_TIMER

#include <signal.h>
#include <sys/epoll.h>
//  服务器程序通常要定期处理非活动连接:给客户端发送一个重连请求,或者关闭该连接。
//  利用alarm函数周期性的触发SIGALRM信号， 该信号的信号处理函数利用管道通知主循环执行定时器链表上的定时器任务
//  ---关闭非活动的连接。

// 采用升序双向链表实现定时器的功能，核心函数tick,
// 它每隔一端固定时间就执行一次，以检测并处理到期的任务。
// 判断定时器任务到期的依据是定时器的expire值小于当前的系统时间。
// 从执行的效率来看，添加定时器的时间复杂度是O(n), 删除定时器的时间复杂度是O(1),执行定时器任务的时间复杂度是O(1).

class util_timer;//提前定义，定时器类
struct client_data //连接资源结构体成员需要用到定时器类
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

//定时器容器，带头尾结点的升序双向链表
// 项目中的定时器容器为带头尾结点的升序双向链表，具体的为每个连接创建一个定时器，
// 将其添加到链表中，并按照超时时间升序排列。执行定时任务时，将到期的定时器从链表中删除。
class sort_timer_lst{
private:
    //头尾结点
    util_timer *head;
    util_timer *tail;
public:
    sort_timer_lst():head(NULL),tail(NULL){}
    //析构函数
    ~sort_timer_lst(){
        util_timer *tmp = head;
        while(tmp){
            head = tmp->next;
            delete tmp;
            tmp = head;
        }
    }
    
    //功能函数
    //添加定时器
    void add_timer(util_timer *timer){
        if(!timer){
            return;
        }
        if(!head){
            head = tail = timer;
            return;
        }
        //如果新的定时器超时时间小于当前头部结点
        //直接将当前定时器结点作为头部结点
        if(timer->expire < head->expire){
            timer->next = head;
            head->prev = timer;
            head = timer;
            return;
        }
        //否则，就调用私有成员函数，调整内部结点
        inner_timer(timer,head);
    }

    //功能函数，调整定时器，当任务发生变化的时候，调整定时器在链表中的位置
    void adjust_timer(util_timer *timer){
        if(!timer){
            return;
        }
        util_timer* temp = timer->next;

        //结点为尾结点，或者，结点调整之后的expire还是小于下一个结点的expire,都不作调整
        if(!temp || (timer->expire<temp->expire)){
            return;
        }
        //如果结点为头结点，则需要把该结点取出来，重新插入到合适的位置
        if(timer == head){
            head = head->next;
            head->prev = NULL;
            timer->next = NULL;
            inner_timer(timer,head);
        }
        //如果改结点是链表中间的结点，则也需要取出来重新插入到合适的位置
        else{
            timer->prev->next = timer->next;
            timer->next->prev = timer->prev;
            inner_timer(timer,timer->next);
        }
    }

    //功能函数，删除定时器
    void del_timer(util_timer *timer){
        if(!timer){
            return;
        }
        //如果链表中只有一个定时器，需要删除该定时器
        if((head == timer)&&(tail == timer)){
            delete timer;
            head = NULL;
            tail = NULL;
            return;
        }
        //如果需要删除的结点是头结点
        if(head==timer){
            head = head->next;
            head->prev = NULL;
            delete timer;
            return;
        }
        //尾结点的情况
        if(tail==timer){
            tail = tail->prev;
            tail->next = NULL;
            delete timer;
            return;
        }
        //被删除的结点在链表内部（排除了以上情况）
        timer->prev->next = timer->next;
        timer->next->prev = timer->prev;
        delete timer;
    }

    //还有一个核心函数,定时任务处理函数
    void tick(){
        if(!head) return;
        //获取当前时间
        time_t  cur = time(NULL);
        util_timer *tmp = head;
        //遍历链表
        while(tmp){
            //升序链表，当前tmp的expire未超时，则后面的也没超时
            if(cur<tmp->expire){
                break;
            }
            //tmp的超时了，需要使用回调函数，执行定时事件，在本项目中，为终端客户端和服务器连接
            tmp->cb_func(tmp->user_data);
            //然后删掉这个tmp
            head = tmp->next;
            if(head){
                head->prev = NULL;
            }
            delete tmp;//回收一下
            tmp = head;
        }
    }

private:
    //私有函数，重载add_timer,用于调整链表内部结点
    void inner_timer(util_timer *timer,util_timer *start_pos){
        util_timer *prev = start_pos;
        util_timer *tmp = prev->next;
        //从tmp的下一个开始遍历，插入timer
        while(tmp){
            if(timer->expire<tmp->expire){
                prev->next = timer;
                timer->next = tmp;
                tmp->prev = timer;
                timer->prev = prev;
                break;
            }
            //继续往后找
            prev = tmp;
            tmp = tmp->prev;
        }
    }
};
#endif