// TCP通信的服务器端-支持并发

#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

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

    // receive
    while (1)
    {
        // accept
        struct sockaddr_in c_addr;
        int len = sizeof(c_addr);
        int c_fd = accept(l_fd, (struct sockaddr *)&c_addr, &len);
        // connect with each client process TCP
        pid_t pid = fork();
        if (pid == 0)
        {
            // get clients' info
            char client_ip[16];
            inet_ntop(AF_INET, &c_addr.sin_addr.s_addr,client_ip,sizeof(client_ip)); //ip
            unsigned short client_port = ntohs(c_addr.sin_port);  //port
            printf("client ip: %s, clinet port: %d \n",client_ip,client_port);

            //get clients' data
            char  recBuf[1024] = {0};
            while ((1))
            {
                if(read(c_fd,&recBuf,sizeof(recBuf)) > 0){
                    printf("recieved data is : %s \n",recBuf);  
                } //简易写法，不考虑断开连接和连接失败

                write(c_fd,&recBuf,strlen(recBuf));
            }
            close(c_fd);
            exit(0);
        }
    }
    close(l_fd); //关闭监听的socket
    return 0;
}