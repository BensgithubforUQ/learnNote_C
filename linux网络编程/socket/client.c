// TCP通信的客户端

#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    //创建套接字
    int fd_sock = socket(AF_INET, SOCK_STREAM, 0);
    //连接服务器端
    struct sockaddr_in server_addr;
    inet_pton(AF_INET, "192.168.19.128", &server_addr.sin_addr.s_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9999);
    int ret_conn = connect(fd_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    //成功连接了服务器，此时服务器端已经阻塞了，等待客户端发送数据
    //向服务器发送数据

    //获取服务端数据
    int num = 5;
    while (num)
    {
        char *data_to_server = "hello, i am client...";
        write(fd_sock, data_to_server, strlen(data_to_server));
        num--;
        char server_buf[1024] = {0};
        int ret_read = read(fd_sock, server_buf, sizeof(server_buf));
        if (ret_read == -1)
        {
            perror("read");
            exit(0);
        }
        else if (ret_read > 0)
        { //表示读到了数据
            printf("received server data： %s\n", server_buf);
        }
        else if (ret_read == 0)
        {
            //客户端断开连接
            printf("server closed connection...");
            break;
        }
    }

    //通信结束，断开连接
    close(fd_sock);

    return 0;
}