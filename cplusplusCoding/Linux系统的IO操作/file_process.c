#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

int main(){
    int ret = access("a.txt",F_OK); //查询文件存在
    if(ret == -1){
        perror("access");
    }
    printf("文件存在 \n");
    int ret1 = chmod("a.txt",0775); //修改文件权限
    if(ret1 == -1){
        perror("chmod");
    }

    int ret2 = truncate("a.txt",20);//调整文件尺寸大小
    if(ret2 == -1){
        perror("truncate");
    }
    return 0;
}