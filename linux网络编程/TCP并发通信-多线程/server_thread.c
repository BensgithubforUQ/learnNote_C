// TCP通信的服务器端-支持并发

#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>


struct SockInfo
{
    /* data */
    int fd; //接受套接字fd
    pthread_t tid;
    struct sockaddr_in addr; //端口号和ip
};

struct SockInfo sockinfos[128];

void *working(void *arg)
{
    //子线程和客户端通信，需要c_fd,客户端信息，线程号
    // get clients' info
    struct SockInfo *s_info = (struct SockInfo *)arg;
    char client_ip[16];
    printf("线程tid为：%ld \n",s_info->tid);
    inet_ntop(AF_INET, &s_info->addr.sin_addr.s_addr, client_ip, sizeof(client_ip)); // ip
    unsigned short client_port = ntohs(s_info->addr.sin_port);                       // port
    printf("client ip: %s, clinet port: %d \n", client_ip, client_port);

    // get clients' data
    char recBuf[1024] = {0};
    while (1)
    {
        int read_ret = read(s_info->fd, &recBuf, sizeof(recBuf));
        if (read_ret > 0)
        {
            printf("recieved data is : %s \n", recBuf);
        } //简易写法，不考虑断开连接和连接失败
        else if (read_ret == -1)
        {
            perror("read");
            exit(-1);
        }
        else if (read_ret == 0)
        {
            printf("client closed...");
            break;
        }

        write(s_info->fd, &recBuf, strlen(recBuf) + 1);
    }
    close(s_info->fd);
    exit(0);
    return NULL;
}


int main()
{
    // set socket
    int l_fd = socket(AF_INET, SOCK_STREAM, 0);
    // struct
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.19.128", &saddr.sin_addr.s_addr);
    saddr.sin_port = htons(9999);

    // bind
    bind(l_fd, (struct sockaddr *)&saddr, sizeof(saddr));

    // listen
    listen(l_fd, 128);

    //初始化数据
    int sockArrayLen = sizeof(sockinfos) / sizeof(sockinfos[0]);
    for (int i = 0; i < sockArrayLen; i++)
    {
        bzero(&sockinfos[i], sizeof(sockinfos[i]));
        sockinfos[i].fd = -1;
        sockinfos->tid = -1;
    }

    // receive 循环等待客户端连接，一旦有客户端连接，创建子线程进行通信
    while (1)
    {
        struct sockaddr_in c_addr;
        int len = sizeof(c_addr);
        int c_fd = accept(l_fd, (struct sockaddr *)&c_addr, &len);

        //创建子线程
        // pthread_t tid;

        //将所需的信息封装成结构体
        struct SockInfo *s_info; //需要创建在堆区
        for (int i = 0; i < sockArrayLen; i++)
        {
            //从其中找到可用的sockinfo元素
            if (sockinfos[i].fd == -1)
            {
                /* code */
                s_info = &sockinfos[i];
                break;
            }
            if (i == sockArrayLen - 1 && sockinfos[i].fd != -1)
            {
                sleep(1);
                i = 0;
            }
        }
        s_info->fd = c_fd;
        memcpy(&s_info->addr, &c_addr, len);
        pthread_create(&s_info->tid, NULL, working, s_info);

        //回收,线程分离
        pthread_detach(s_info->tid);
    }
    close(l_fd);
    return 0;
}