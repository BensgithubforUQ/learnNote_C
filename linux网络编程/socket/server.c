// TCP通信的服务器端

#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

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
    //通信
    //接受客户端连接
    struct sockaddr_in clientAddr;
    int len = sizeof(clientAddr);
    int ret_acc = accept(listen_fd, (struct sockaddr *)&clientAddr, &len); //如果成功，返回的是一个fd，是客户端的数据
    if (ret_acc == -1)
    {
        perror("accept");
        exit(0);
    }
    //输出客户端信息
    char client_ip[16];
    inet_ntop(AF_INET, &clientAddr.sin_addr.s_addr, client_ip, sizeof(client_ip));
    unsigned short client_port = ntohs(clientAddr.sin_port);
    printf("client ip:%s, client port: %d \n", client_ip, client_port);

    //获取客户端数据
    for (int i = 0; i < 5; i++)
    {
        char client_buf[1024] = {0};
        int ret_read = read(ret_acc, client_buf, sizeof(client_buf));
        if (ret_read == -1)
        {
            perror("read");
            exit(0);
        }
        else if (ret_read > 0)
        { //表示读到了数据
            printf("received client data： %s\n", client_buf);
        }
        else if (ret_read == 0)
        {
            //客户端断开连接
            printf("client closed connection...");
            break;
        }

        //给客户端发送数据
        char *data_to_client = "hello, i am server...";
        write(ret_acc, data_to_client, strlen(data_to_client));
    }

    //关闭文件描述符
    close(ret_acc);
    close(listen_fd);
    return 0;
}