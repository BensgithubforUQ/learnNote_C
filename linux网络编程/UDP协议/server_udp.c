/*
UDP,回声服务器端
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(){

    int server_sock = socket(PF_INET, SOCK_DGRAM, 0); // UDP协议的套接字初始化和定义
    if (server_sock == -1)
        printf("socket create error...\n");

    int str_len;
    socklen_t client_addr_size;
    struct sockaddr_in server_addr, client_addr;
    memset(&server_addr, 0, sizeof(server_addr)); //初始化服务器信息
    inet_pton(AF_INET,"192.168.19.128",&server_addr.sin_addr.s_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = ntohs(9999);

    bind(server_sock, (struct sockaddr *)&server_addr,sizeof(server_addr)); //绑定
    char msg[30];
    while (1)
    {
        /* code */
        client_addr_size = sizeof(client_addr);
        str_len = recvfrom(server_sock, msg, 50, 0, (struct sockaddr *)&client_addr, &client_addr_size);
        //成功时返回接受的字节数，失败返回-1
        if(str_len>0) printf("读到了%d个字节的数据,信息是:%s\n",str_len,msg);
        else if(str_len == 0) printf("无可读？\n");
        else if(str_len == -1) printf("错误\n"); 
        sendto(server_sock, msg, str_len, 0, (struct sockaddr *)&client_addr,client_addr_size);
    }
    close(server_sock);
    return 0;
}