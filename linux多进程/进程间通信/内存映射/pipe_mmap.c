#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <wait.h>

int main()
{

    /*
    void * mmap(void *__addr, size_t __len, int __prot, int __flags, int __fd, off_t __offset)
    参数：
        *addr NULL，由内核指定
        length 不为0，一般用文件的长度（stat lseek获取文件长度
        prot，对申请的内存映射区的操作：
        prot_exec 可执行权限
        prot_read 读权限
        prot_write 写权限
        prot_none 没有权限
        要操作映射内存必须要有读权限，或者读写权限都有。
        flags
            map-shared 映射区会自动和磁盘文件同步，进程通信必须设置
            map-private 不同步，对于源文件不会修改，会拷贝一个新的文件
        fd 需要映射操作的文件的文件描述符
            文件大小需要大于0.用open获得
        offset 偏移量一般不用，必须是4k的整数倍，0意味着不偏移，从头开始

        不阻塞
    */
    int fd = open("test.txt", O_RDWR);                                       //获取fd
    int size = lseek(fd, 0, SEEK_END);                                       //获取文件的大小
    void *ptr = mmap(NULL, size, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0); //创建内存映射区
    if (ptr == MAP_FAILED)
    {
        perror("mmap");
        exit(0);
    }
    //创建子进程
    pid_t pid = fork();
    if (pid > 0)
    {
        printf("父进程,pid: %d\n",getpid());
        wait(NULL); //等子进程结束之后再调用后面的代码
        char buf[64];
        strcpy(buf, (char *)ptr);
        printf("read data : %s, pid: %d\n", buf,getpid());
        
    }
    else if (pid == 0)
    {
        printf("子进程,pid: %d, ppid : %d\n",getpid(),getppid());
        strcpy((char *)ptr, "hellow, child\n");
    }
    munmap(NULL,size);
    return 0;
}