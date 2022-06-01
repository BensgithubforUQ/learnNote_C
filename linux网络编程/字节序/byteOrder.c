/*
字节序0x0102
字节在内存中存储的顺序
小端字节序，数据的高位字节存储在内存的高位，低位字节存储在内存的低位 02 01
大端字节序，数据的低位字节存储在内存的高位，高位字节存储在内存的低位。01 02

网络字节序，TCP/IP中规定好的一种数据表示格式，和具体的cpu类型操作系统无关。
可以保证数据在不同主机之间传输的时候能够被正确的解释，网络字节顺序采用大端排序方式

bsd socket还封装了转化接口。
*/

#include <stdio.h>
#include <arpa/inet.h>

int main()
{
    union
    {                              //共用体
        short value;               // 2字节
        char bytes[sizeof(short)]; // char[2]
    } test;

    test.value = 0x0102;

    if ((test.bytes[0] == 1) && (test.bytes[1] == 2))
        printf("host是大端字节序\n");
    else if ((test.bytes[0] == 2) && (test.bytes[1] == 1))
        printf("host是小端字节序\n");
    else
        printf("未知\n");

    //h - host主机， to - 转化， n - network网络字节序，short，long短型，长型
    //htons 主机转化到网络字节序（本主机是小端字节序，转化为，大端字节序）
    unsigned short a = 0x0102;
    unsigned short b = htons(a);
    printf("host : a : %x\n",a);
    printf("网络字节序 ：b : %x\n",b);
    //htonl 转化IP
    char buf[4] = {192,168,1,100};
    int c = *(int *)buf;
    int d = htonl(c);
    unsigned char *p = (char *)&d;
    printf("转换192 168 1 100 to IP: %d %d %d %d\n",*p,*(p+1),*(p+2),*(p+3));
    //htons和ntohl 跟 上面类似

    return 0;
}