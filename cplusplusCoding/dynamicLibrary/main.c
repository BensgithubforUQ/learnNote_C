#include <stdio.h>
#include "head.h"

int main()//g++ main.c -o app -I include/ -L lib/ -l calc 编译方法
{   //动态库在进程需要用到动态库中的方法的时候，才会加载，因此节约内存，并且易于更新发布和部署
    //因此加载速度比静态库稍微慢一点，发布程序的时候，需要提供依赖的动态库。
    //g++ -c -fpic add.c div.c mult.c sub.c -I ../include/ 无链接的对象文件生成
    //g++ -shared add.o div.o mult.o sub.o -o libcalc.so 动态库生成
    //直接编译得到的app文件不可执行，找不到动态库，
    //所以这里在app文件执行的时候，链接阶段找不到动态库。
    //用ldd app来查询依赖库。
    //这时候，就需要用系统的动态加载器来获取动态库的绝对路径。
    //可以通过配置环境变量，将该动态库加入到环境变量中，让动态加载起获取绝对路径的方式
    //这样可以让app找到动态库，配置命令如下（临时，这个关掉终端就又不认了）
    //export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/ben/Linux/learnNote_C/cplusplusCoding/dynamicLibrary/lib
    //所以用别的方法
    //用户级别的配置：
    //用cd进入home目录，找环境变量配置文件.bashrc
    //在文件末尾加入上述的环境变量配置，就可以运行（记得 source .bashrc）
    //系统级别的配置方法：
    //在/etc/profile中加入环境变量的配置
    
    int a = 20;
    int b = 12;
    printf("a = %d, b = %d\n", a, b);
    printf("a + b = %d\n", add(a, b));
    printf("a - b = %d\n", subtract(a, b));
    printf("a * b = %d\n", multiply(a, b));
    printf("a / b = %f\n", divide(a, b));
    return 0;
}
