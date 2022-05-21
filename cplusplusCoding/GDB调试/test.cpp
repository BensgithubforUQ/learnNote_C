#include <iostream>
using namespace std;

int test(int a);

int main(int argc, char *argv[]){
    int a,b;
    cout<<"argc = "<<argc<<endl;
    //GDB 调试命令，关闭-o的编译器优化选项，开旗调试选项-g wall可以收集所有的warning
    // g++ -g -Wall program.c -o program
    //-g选项可以在可执行文件中加入源代码的信息
    //gdb xxx
    //quit
    //set args 10 20 (设置参数)
    //show args （获取参数）
    //help
    //查看当前文件代码
    //list/l （默认位置显示）
    //list/l 行号 （从指定位置显示）
    //list/l 函数名 （从指定函数显示）
    //查看非当前文件代码
    //list/l 文件名：行号
    //list/l 文件名：函数名
    //show list/listsize 
    //set list/listsize
    //break +行数
    //break 行数 if ? == ? （条件断点）
    //info break断点信息
    //disable enable delete + num
    //start run / continue
    //next 不进函数体的一步步执行
    //print，ptype
    //step 一步步执行
    //finish 跳出函数体
    //dispaly num 自动打印
    //info display 
    //undisplay 
    //set var  变量名 = 变量值
    //until 跳出循环
    if(argc<3){
        a = 10;
        b = 30;
    }
    else{
        a = atoi(argv[1]);
        b = atoi(argv[2]);
    }
    cout<<"a = "<<a<<", b = "<<b<<endl;
    cout<<"a + b = "<<a+b<<endl;
    for(int i = 0;i<a;++i){
        int res = test(i);
        cout<<"the result is :"<<res<<endl;
    }
    printf("end of the program\n");
    return 0;
}

int test(int a){
    int num  = 0;
    for(int i =0;i<a;++i) num+= i;
    return num;
}