#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

int main(){
    //int fcntl(int fd, int cmd, ... /* arg */ );
    //...是可变参数,cmd是表示对文件描述符如何操作
    /*
    F_DUPFD, int ret = fcntl(fd, F_DUPFD);复制文件描述符，复制的是第一个参数fd，
    得到一个新的

    F_GETFL,获得指定文件描述符文件状态flag（file status flags）获取的flag和open函数
    传递的flag是同一个东西。

    F-SETFL,设置文件描述符文件状态flag
    必选，O_RDONLY,O_WRONLY,O_RDWR,不可以修改
    可选，O_APPEND(追加数据),O_NONBLOCK（设置成非阻塞****重点）;

    */
    //复制文件描述符（F_DUPFD），获取和设置文件描述符(F_GETFL，F_SETFL)

    //复制文件描述符
    int fd = open("text_fcntl.txt", O_RDWR | O_CREAT);
    int fd1 = fcntl(fd,F_DUPFD);

    //修改或者改变文件的文件描述符状态flag
    //先获取
    int flag = fcntl(fd1, F_GETFL);
    flag |= O_APPEND;
    //然后设置
    int ret = fcntl(fd1,F_SETFD,flag);
    if(ret == -1){
        perror("fcntl");
        return -1;
    }
    char * str = "hello world";
    write(fd1,str,strlen(str));
    close(fd1);
    return 0;
}