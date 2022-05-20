#include <stdio.h>
#include "head.h"

int main() //g++ main.c -o app -I ./include/ -l calc -L ./lib //compile command
{
    //Makefile书写规则
    //目标...: 依赖 ...
    //  命令（shell）
    //  ...
    int a = 20;
    int b = 12;
    printf("a = %d, b = %d\n", a, b);
    printf("a + b = %d\n", add(a, b));
    printf("a - b = %d\n", subtract(a, b));
    printf("a * b = %d\n", multiply(a, b));
    printf("a / b = %f\n", divide(a, b));
    return 0;
}
