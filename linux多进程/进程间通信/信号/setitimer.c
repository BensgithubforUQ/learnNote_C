#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>

int main(){
    //int setitimer(int which, const struct itimerval *new_value, struct itimerval *old_value);
    struct itimerval new_value;
    new_value.it_interval.tv_sec = 2;//持续时间
    new_value.it_interval.tv_usec = 0;

    new_value.it_value.tv_sec = 3; //延迟
    new_value.it_value.tv_usec = 0;

    int ret = setitimer(ITIMER_REAL,&new_value,NULL);//非阻塞
    if(ret == -1){
        perror("setitimer");
        exit(0);
    }
    getchar();
    return 0;

}
