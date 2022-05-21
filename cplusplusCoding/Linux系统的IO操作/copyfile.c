#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    int a_op = open("a.txt",O_RDONLY);
    int b_op = open("b.txt",O_WRONLY | O_CREAT,0664);
    //ssize_t read(int fd, void *buf,size_t cout)
    //fd:文件描述符
    //buf:需要读取数据存放的地方，数组的地址（传出参数）
    //count指定数组的大小，最大容量。
    //同样如果读不到，就返回-1，并且把errno设定成一个值。
    //如果成功，>0: 返回实际读到的字节数，表示还没读完
    // = 0：表示文件已经读完了

    //ssize_t write(int fd, const void *buf, size_t count);
    //buf:要往磁盘写入的数据
    //count要写的数据的实际大小，意思是写多少。
    //成功，返回实际写入的字节数
    //失败的话和上面那个一样。
    char buf[1024] = {0}; //初始化一个buf
    int len = 0;
    do{
        len = read(a_op,buf,sizeof(buf)); //读，返回从a读了多少个
        write(b_op,buf,len); //写，返回了多少个往b里写多少个
    }while(len > 0); //只要len ！= 0则还没读完

    close(a_op);
    close(b_op); //完事儿了关一下
    return 0;
}