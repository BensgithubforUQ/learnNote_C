#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    struct stat statebuf;
    int ret = stat("a.txt",&statebuf);
    if(ret == -1) perror("stat");
    //statebuf+宏，可以返回想要的信息
    else printf("size: %ld\n",statebuf.st_size);
    return 0; 
}