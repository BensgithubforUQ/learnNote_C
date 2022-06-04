// TCP通信的服务器端

#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/select.h>

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
    int ip_addr = inet_pton(AF_INET, "127.0.0.1", &sockAddr.sin_addr.s_addr);
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

    //定义reads
    fd_set reads, cpy_reads;
    struct timeval timeout;
    FD_ZERO(&reads);
    FD_SET(listen_fd, &reads);
    int fd_max = listen_fd; //当前最大的文件描述符个数
    int fd_num = 0;         //当前文件描述符个数
    //获取客户端数据
    while (1)
    {
        //每次都回归原始状态
        cpy_reads = reads;
        //设置等待参数
        // timeout.tv_sec = 5;
        // timeout.tv_usec = 5000;
        //设置select监听
        fd_num = select(fd_max + 1, &cpy_reads, NULL, NULL, NULL);
        if (fd_num == -1)
        {
            perror("select");
            break; //如果失败，退出循环
        }
        else if (fd_num == 0)
        {
            continue; //如果fd_num == 0意味着没有文件描述符变化，接下来的代码都不用执行
        }
        else if (fd_num > 0)
        {
            /* code */
            //如果文件描述符有变化
            for (int i = 0; i < fd_max + 1; i++)
            {
                if (FD_ISSET(i, &cpy_reads))
                { //检查i是否在cpy_reads中，是返回1，不是返回0
                    //如果是，判断是否是监听套接字
                    if (i == listen_fd)
                    {
                        //建立新的连接
                        //通信
                        //接受客户端连接
                        struct sockaddr_in clientAddr;
                        int len = sizeof(clientAddr);
                        int ret_acc = accept(listen_fd, (struct sockaddr *)&clientAddr, &len); 
                        //如果成功，返回的是一个fd，是客户端的数据
                        FD_SET(ret_acc, &reads); //建立新连接，向fd_set里添加新的文件描述符
                        if (fd_max < ret_acc)
                            fd_max = ret_acc; //更新fd_max大小
                        printf("new connected clinet: %d \n", ret_acc);
                    }
                    else
                    {
                        //如果不等于监听套接字，则是已存在的连接
                        char client_buf[1024] = {0};
                        int ret_read = read(i, client_buf, sizeof(client_buf));
                        if (ret_read == -1)
                        {
                            perror("read");
                            exit(0);
                        }
                        else if (ret_read > 0)
                        { //表示读到了数据
                            printf("received client data： %s\n", client_buf);
                            write(i, client_buf, ret_read); // echo回声
                        }
                        else if (ret_read == 0)
                        {
                            //客户端断开连接
                            FD_CLR(i, &reads); //读完了
                            close(i);          //释放该文件描述符
                            printf("client closed connection...");
                        }
                    }
                }
            }
        }

        // //给客户端发送数据
        // char *data_to_client = "hello, i am server...";
        // write(ret_acc, data_to_client, strlen(data_to_client));
    }

    //关闭文件描述符
    // close(ret_acc);
    close(listen_fd);
    return 0;
}