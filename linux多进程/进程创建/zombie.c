 #include <sys/types.h>
 #include <unistd.h>
 #include <stdio.h>

 int main(){
     //fork()  creates a new process by duplicating the calling process.  
     //The new process is referred to as the child process.  
     //The calling process is referred to as the parent process.
     int num = 0;
     pid_t pid = fork(); //fork函数返回两次返回值，一次在父进程，一次在子进程
     //fork就是叉子嘛，分叉，叉出去父进程和子进程，形成进程树
     //父进程中返回创建子进程的id，区分父进程和子进程通过判断fork的返回值
     //父进程中返回-1，表示创建子进程失败，并且设置errornum
     if(pid>0){
         //pid大于0,就是父进程，返回的是子进程的id
         printf("pid : %d \n",pid);
         while(1){
             num += 10;
             printf("this is a parent process,pid: %d, ppid: %d, num = %d\n",getpid(),getppid(), num);
             sleep(1);
         }
         
     }
     if(pid == 0){
         //等于0，则是子进程
         sleep(1); //orphan进程，这里加个sleep就会出现父进程结束子进程未结束的情况
         //这时候子进程的父进程就会被内核设置为inti，ppid = 1
         //然后，因为这时候子进程的内核去的文件操作符还和原来的父进程是一样的
         //因此还是在原来的终端中进行文件IO操作。
         //这也是彰显了孤儿进程和原父进程的关系吧，大概。
         num += 100; 
         printf("this is a child process,pid: %d, ppid: %d, num = %d\n",getpid(),getppid(), num);
     }
     for(int i =0;i<5;i++){
         ++num;
         printf("i: %d,pid : %d, num: %d\n",i,getpid(),num);//可以发现进程交错运行。
     }
     return 0;
 }
 /*写时拷贝指的是子进程的页表项指向与父进程相同的物理页，
 这也只需要拷贝父进程的页表项就可以了，不会复制整个内存地址空间，
 同时把这些页表项标记为只读。如果父子进行都不对页面进行操作，那么便一直共享同一份物理页面。
 只要父子进程有一个尝试进行修改某一个页面，那么就会发生缺页异常（page fault）。
 那么内核便会为该页面创建一个新的物理页面，并将内容复制到新的物理页面中，
 让父子进程真正地各自拥有自己的物理内存页面，并将页表中相应地页表项标记为可写。
*/