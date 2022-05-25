#include <unistd.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

int main(){
    //文件描述符，前三个，，std cin，std cout，std cerr
    int fd = open("a.txt",O_RDONLY); //读取一个文件，返回一个文件描述符
    int new_file_descriptor = dup(fd);//从空闲的问价描述符表中找一个最小的返回。从3开始。
    //dup有点浅拷贝的意思，其实是换了个名字。
    if(new_file_descriptor == -1){
        perror("dup");
    }
    printf("fd:%d, new_file_descriptor:%d \n",fd,new_file_descriptor);
    close(fd);

    char * text_1 = "hello world ";
    int ret = write(new_file_descriptor,text_1,strlen(text_1));
    if(ret == -1) perror("write");

    close(new_file_descriptor);
    return 0;
}