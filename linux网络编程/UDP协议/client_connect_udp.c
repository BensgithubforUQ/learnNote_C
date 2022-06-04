/*
UDP,回声客户端
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

int main(){
    int sock;
    char msg[BUF_SIZE];
    int str_len;
    struct sockaddr_in serv_adr;
    sock = socket(PF_INET,SOCK_DGRAM,0);
    if(sock == -1) printf("socket error...\n");

    memset(&serv_adr,0,sizeof(serv_adr));
    inet_pton(AF_INET,"192.168.19.128",&serv_adr.sin_addr.s_addr);
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_port = ntohs(9999);

    connect(sock,(struct sockaddr *)&serv_adr,sizeof(serv_adr)); //建立连接，缩短UDP套接字注册和删除目标IP和端口号的时间

    while (1)
    {
        /* code */
        fputs("insert msg(q to quit):",stdout);

        fgets(msg,sizeof(msg),stdin);

        if(!strcmp(msg,"q\n") || !strcmp(msg,"Q\n")){
            break;
        } 
        write(sock,msg,strlen(msg)); //connet之后可以用write和read，而不必须用recvfrom和sendto
        str_len = read(sock,msg,strlen(msg)-1);
        msg[str_len] = 0;
        printf("msg back from server : %s\n",msg);
    }
    close(sock);
    return 0;
}