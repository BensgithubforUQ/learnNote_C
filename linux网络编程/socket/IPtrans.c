//IP地址转换
//一般IP是四个字节的数字，但是一般用字符串来表示198.196.0.0
//字符串ip-整数，主机，网络字节序的转化

#include <stdio.h>
#include <arpa/inet.h>

int main(){
    //p:点分十进制的IP字符串，n：表示network，网络字节序（int）
    // int inet_pton(int af,const char *src, void *dst);
    //af,地址族。src，需要转换的点分十进制的ip字符串，dst，传出参数
    //const char *inet_ntop(int  af, const void *src, char* dst, socklen_t size);
    //size，dst的大小。返回值，返回转换后的数据的地址，和dst一致。

    //创建一个ip字符串，点分十进制的IP地址字符串
    char buf[] = "192.168.1.1";
    unsigned int num = 0;
    //将点分十进制的IP字符串转化为网络字节序的整数
    inet_pton(AF_INET,buf,&num);
    unsigned char *p = (unsigned char *)&num;
    printf("转换后的ip地址是： %d %d %d %d\n",*p,*(p+1),*(p+2),*(p+3));

    //将网络字节序的整数，转化为点分十进制的IP字符串
    char ip[16] = "";
    const char * str = inet_ntop(AF_INET,&num,ip,16);
    printf("ip str: %s\n",str);
    return 0;

}