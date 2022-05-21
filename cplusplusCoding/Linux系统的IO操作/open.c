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
    //errno:属于linux系统函数库，库里的全局变量，记录的是最近的错误号。
    //可以用函数perror（man 3标准c库里的函数）来打印errno对应的错误描述
    //void perror(const char *s)
    int fd = open("a.txt",O_RDONLY); //返回一个文件描述符
    if(fd == -1) perror("open");
    else printf("无报错\n");
    close(fd); //释放文件描述符，并且让这个描述符可以被重用
    return 0;
}