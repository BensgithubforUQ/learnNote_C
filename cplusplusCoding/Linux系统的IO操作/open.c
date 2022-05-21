#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
//前两个库，里面存了一堆宏。
//fcntl.h是存具体的方法的库

int main(){
    //int open(const char *pathname, int flags);
    //flags 对文件的操作权限的设置
    //O_RDONLY, O_WRONLY, O_RDWR,这三个互相互斥，返回一个文件描述符，如果失败，返回-1
    //这些事可选的flags：
    //O_APPEND,O_CREAT...
    //mode:八进制数，表示用户对文件的权限，比如0777，但是最终的权限是mode & ~umask（掩码）
    //0777 mode -> 111 111 111
    //0775 umask -> 111 111 101
    //& ->按位与运算，0和任何数都为0 ：111 111 101
    //umask的作用就是抹去部分权限，umask可以用umask + 值来设定。
    //errno:属于linux系统函数库，库里的全局变量，记录的是最近的错误号。
    //可以用函数perror（man 3标准c库里的函数）来打印errno对应的错误描述
    //void perror(const char *s)
    int fd = open("a.txt",O_RDONLY); //返回一个文件描述符
    if(fd == -1) perror("open");
    else printf("无报错\n");
    close(fd); //释放文件描述符，并且让这个描述符可以被重用
    fd = open("creat.txt",O_RDWR | O_CREAT, 0777);
    if(fd == -1) perror("open");
    else printf("无报错,成功创建\n");
    close(fd);
    return 0;
}