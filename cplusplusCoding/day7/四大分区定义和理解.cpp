#include <iostream>
#include <string>
using namespace std;

//内存分区，一共分四区。不同区域存放的数据，赋予不同的生命周期，给我们更大的灵活编程。
//分别是：
//代码区：存放函数体的二进制代码，由操作系统进行管理的。
//储存的是cpu的机器指令。
//代码区是共享的，共享的目的是对于频繁被执行的程序，只需要在内存中有的一份代码即可。
//代码区是只读的，使其只读的原因是防止程序意外的修改了指令。

//全局区：是存放全局变量和静态变量的区域，以及常量。字符常量和其他常量也存放于次。
//该区域的数据在程序结束后由操作系统释放。
//这些数据的生命周期不由我们控制。
//这些数据没有申明和定义在函数体内
int g_a = 10; //全局变量，存放在全局区里。
int g_b = 10; //全局变量，存放在全局区里。
const int c_g_a = 10;//const 修饰的全局变量
const int c_g_b = 10;//const 修饰的全局变量

//栈区：由编译器自动分配释放，存放函数的参数值，局部变量等。
//注意事项，不要返回局部变量的地址，栈区开辟的数据由编译器自动释放。

int *test() {//测试栈区数据用
	int x = 10;
	return &x;
}
//堆区：由程序员分配释放，如果程序员不释放，则在程序结束的时候由操作系统回收。
//在c++中主要由new来在堆区开辟内存。
int* func() {
	int *x = new int(10);//这个x指针是储存在栈上的局部变量，而指向了堆区、
	return x;
}
int main() {
	int *x = func();
	cout << "尝试打印堆区的局部变量的地址的位置储存的值" << *x << endl;
	delete(x);//释放堆区的内存之后，就不能再读这个数据了。
	//cout << "尝试打印堆区的局部变量的地址的位置储存的值" << *x << endl;
	//利用new在堆区创建数组：
	int *arr = new int[10];
	for (int i = 0; i < 10;i++) {
		arr[i] = i;
	}
	for (int i = 0; i < 10; i++) {
		cout << arr[i] <<" ";
	}
	cout << endl;
	//释放堆区的数组：用delete[]；
	delete[] arr;
	//利用new在堆区创建二维数组：
	int size1= 10,size2 = 10;
	cin >> size1 >> size2;
	int** array_2d = new int* [size1];//size1是二维数组的前一个size，size2第二维的size
	for (int i = 0; i < size1; i++) {
		array_2d[i] = new int[size2];
		for (int j = 0; j < size2; j++) {
			array_2d[i][j] = i * j;
		}
	}
	//重点中的重点
	for (int i = 0; i < size1; i++) {
		for (int j = 0; j < size2; j++) {
			cout << array_2d[i][j] << " ";
		}
		cout << endl;
	}
	int* p = test();
	cout << "尝试打印栈区的局部变量的地址位置储存的值" << *p << endl;
	cout << "尝试打印栈区的局部变量的地址位置储存的值" << *p << endl; 
	//可以发现取不到10，证明不可能在函数调用完之后取到栈区的局部变量。
	int a = 1, b = 2; //在函数体内定义的局部变量，存放在代码区里面
	cout << "局部变量a的地址为：" << (int)&a << endl;
	cout << "局部变量b的地址为：" << (int)&b << endl;
	cout << "全局变量g_a的地址为：" << (int)&g_a << endl;
	cout << "全局变量g_b的地址为：" << (int)&g_b << endl;
	//打印完之后发现，不同区的变量在内存条里面的地址完全不一样。

	static int s_a = 10;//静态变量，虽然在函数体里面，但是也是全局区的数据。
	static int s_b = 10;
	cout << "静态变量s_a的地址为：" << (int)&s_a << endl;
	cout << "静态变量s_b的地址为：" << (int)&s_b << endl;

	//常量也是储存在全局区的
	//字符串常量，只要是双引号修饰的字符串都是常量。
	cout << "字符串常量的地址为：" << (int)"hello world" << endl;
	cout << "字符串常量的地址为：" << (int)"happy world" << endl;
	
	//const 修饰的全局变量 和 修饰的局部变量
	//const 修饰的局部变量，放在代码区，而不是全局区。
	const int c_l_a = 10;
	const int c_l_b = 10;
	cout << "const修饰的全局变量，即全局常量" << (int)&c_g_a << endl;
	cout << "const修饰的全局变量，即全局常量" << (int)&c_g_b << endl;
	cout << "const修饰的局部变量" << (int)&c_l_a << endl;
	cout << "const修饰的局部变量" << (int)&c_l_b << endl;
	return 0;
}
//结论：c++中在程序运行之前分为全局区和代码区。
//代码区是共享和只读的。
//全局区中存着全局变量，静态变量，和常量（全局常量）。
//常量区中存放const修饰的全局常量，和，字符串常量。


