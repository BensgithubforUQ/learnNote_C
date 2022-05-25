#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(){
    int ret = mkdir("aaa",0777); //创建一个目录 对应的rmdir是删除home目录。
    if(ret == -1){
        perror("mkdir");
        //return -1;
    }
    ret = rename("aaa","bbb"); //目录改名
    if(ret == -1){
        perror("rename");
        //return -1;
    }
    char buf[128]; //buf是个传出参数,指针传参，实参。
    getcwd(buf,sizeof(buf)); //修改进程的工作目录
    //比如在本目录上启动程序，则进程工作目录就在本目录
    //可以通过这个函数换到其他目录
    
    printf("当前的工作目录是：%s\n",buf);//buf是个传出参数
    ret = chdir("/home/ben/Linux/learnNote_C/cplusplusCoding/Linux系统的IO操作/bbb");
    if(ret == -1){
        perror("chdir");
        return -1;
    }

    int fd = open("chdir.txt", O_CREAT | O_RDWR, 0777); //在新目录创个文件
    if(fd == -1){
        perror("open");
        return -1;
    }
    getcwd(buf,sizeof(buf)); 
    printf("当前的工作目录是：%s\n",buf);
    return 0;
}