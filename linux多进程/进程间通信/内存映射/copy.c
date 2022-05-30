#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main(){
    //1.对原始文件进行内存映射
    int fd = open("test.txt",O_RDWR);
    int size = lseek(fd,0,SEEK_END);
    //2.c创建一个新文件
    int fd1 = open("newTxt.txt",O_RDWR | O_CREAT, 0664);
    //对新文件进行扩展，因为内存映射length不能为0
    truncate("newTxt.txt",size);
    write(fd1," ",1);
    //创建内存映射
    void *ptr = mmap(NULL,size,PROT_READ,MAP_SHARED,fd,0);
    void *ptr1 = mmap(NULL,size,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
    if(ptr == MAP_FAILED){
        perror("mmap");
        exit(0);
    }
    if(ptr1 == MAP_FAILED){
        perror("mmap");
        exit(0);
    }
    memcpy(ptr1,ptr,size);
    munmap(ptr1,size); //释放
    munmap(ptr,size);
    close(fd1); //释放
    close(fd);
    return 0;
}