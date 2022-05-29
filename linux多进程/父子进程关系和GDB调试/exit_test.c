#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    printf("hello \n"); // \n会刷新IO缓冲区
    printf("world");

    //exit(0); //会刷新IO缓冲区，然后调用_exit(0); 标准c库的函数
    _exit(0); //不会刷新IO缓冲区,linux的系统函数

}