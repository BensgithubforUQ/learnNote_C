// #include <sys/types.h>
// #include <unistd.h>
// off_t lseek(int fd, off_t offset, int whence);
// offset 偏移量
// whence ：SEEK_SET,SEEK_END,SEEK_CUR 设置文件的偏移量
/*作用
1.移动文件指针到头文件 lseek(fd,0,SEEK_SET);
2.获取当前文件指针所在位置 lseek(fd,0,SEEK_CUR);
3.获取文件长度 lseek(fd,0,SEEK_END);
4.拓展文件长度 lseek(fd,100,SEED_END);
*/
// #include <stdio.h>
// int fseek(FILE *stream, long offset, int whence);

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
    int fd = open("hello.txt",O_RDWR | O_CREAT, 0777);
    int ret = lseek(fd, 100, SEEK_SET);
    if(fd == -1 || ret == -1) {
        perror("fd") ;
        perror("lseek");
    }
    else{
        write(fd,"？",1);//写入一个字符，但是中间挪的100下，也会自动填充空字符
        printf("everything is alright.\n");
    }
    close(fd);
    return 0;
}