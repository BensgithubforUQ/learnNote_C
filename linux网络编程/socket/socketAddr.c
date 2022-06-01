//socket地址是一个结构体，封装端口号和IP等信息
//客户端 -> 服务器 （port, IP）
//在后续socket相关api里需要使用该结构体（socket地址）

/*
sockaddr：通用socket地址，开发一般不用
struct sockaddr{
    sa_family_t sa_family; //地址族类型，和协议族类型对应
    //（PF_UNIX,AF_UNIX,unix本地域协议族）
    //（PF_INET,AF_INEX,TCP/IPV4协议族）
    //（PF_INET6,AF_INEX6,TCP/IPV6协议族）

    cahr sa_data[14]; //存放socket地址值，但是不同的协议族的地址值具有不同的含义和长度
    //PF_UNIX 文件路径名，长度可以108字节
    //PF_INET ,16bit的端口号和32位的ipv4地址，一共6个字节

};
typedef unsigned short int sa_family_t;
*/

/*专用的socket地址
端口号，ip地址等都是分开定义
使用的时候直接赋值。
然后在使用的时候，会自动的强制转化为通用的socketaddr
struct sockaddr_in{
    sa_family_t sa_family; //地址族类型，和协议族类型对应
    //（PF_UNIX,AF_UNIX,unix本地域协议族）
    //（PF_INET,AF_INEX,TCP/IPV4协议族）
    //（PF_INET6,AF_INEX6,TCP/IPV6协议族）

    in_port_t sin_port; //端口号
    struct in_addr sin_addr; //IP地址

    unsigned char sin_zero(...)//填充的部分


};

struct in_addr{
    in_addr_t s_addr;
}
所有专用的socket地址类型变量都会在使用的时候自动强制转化为通用的socket地址类型。
*/