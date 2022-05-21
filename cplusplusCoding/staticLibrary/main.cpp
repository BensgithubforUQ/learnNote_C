#include <iostream>
#include "head.h"

int main() //g++ main.c -o app -I ./include/ -l calc -L ./lib //compile command
{
//     Linux : libxxx.a
// lib : 前缀（固定）
// xxx : 库的名字，自己起
// .a : 后缀（固定）
    int a = 20;
    int b = 12;
// Windows : libxxx.lib
// 静态库的制作：
// ◆ gcc 获得 .o 文件
// ◆ 将 .o 文件打包，使用 ar 工具（archive）
// ar rcs libxxx.a xxx.o xxx.o
// r – 将文件插入备存文件中
// c – 建立备存文件
// s – 索引
    printf("a = %d, b = %d\n", a, b);
    printf("a + b = %d\n", add(a, b));
    printf("a - b = %d\n", subtract(a, b));
    printf("a * b = %d\n", multiply(a, b));
    printf("a / b = %f\n", divide(a, b));
    return 0;
}
