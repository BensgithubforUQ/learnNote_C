#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>

int  main(){
    //创建一个共享内存
    int shmid = shmget(100,0,IPC_CREAT);//获取共享内存
    printf("shmid: %d\n",shmid);
    //和当前进程进行关联
    void *ptr = shmat(shmid,NULL,0);//SHM_RDONLY 单 读权限，0为读写权限
    char *str = "hello world";
    //读数据
    printf("%s\n",(char *)ptr);

    printf("按任意键继续...");
    getchar();
    //解除关联
    shmdt(ptr);
    //删除共享内存
    shmctl(shmid,IPC_RMID,NULL);//ipc_rmid只是标记删除，等所有和该共享内存关联的进程都与其解除关联，就删除
    return 0;
}