#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>


int getFileNum(const char *path);

int main(int argc,char * argv[]){//读取某个目录下所有普通文件的个数
    if(argc<2){
        printf("%s path\n",argv[0]);
        return -1;
    }
    int num = getFileNum(argv[1]);
    printf("普通文件的个数为 ：%d\n",num);
    return 0;
}

//获取目录下文件的个数
int getFileNum(const char *path){
    DIR *dir = opendir(path);
    if(dir == NULL){
        perror("opendir");
        exit(0);
    }
    struct dirent *ptr; //读到的文件的信息的结构体指针
    int countFileNumb = 0; //记录普通文件的个数
    while((ptr =readdir(dir)) != NULL){ //这个指针好像会自己增加诶，就自己往下读
        //获取名称
        char * dname = ptr->d_name;
        //h忽略.和..
        if(strcmp(dname,".") == 0 || strcmp(dname, ".." )== 0) continue;

        if(ptr->d_type == DT_DIR){
            //读到的是个目录
            char newpath[256];
            sprintf(newpath,"%s/%s",path,dname);
            countFileNumb += getFileNum(newpath);
        }

        if(ptr->d_type == DT_REG){
            //读到的是个普通文件
            ++countFileNumb;
        }
    }
    closedir(dir);
    return countFileNumb;
    
} 