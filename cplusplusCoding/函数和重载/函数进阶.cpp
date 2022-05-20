#include <iostream>
#include <string>
using namespace std;

int func(int a, int b, int c) {
	int sum = a + b + c;
	return sum;
}

//注意事项，如果某个位置已经有了默认参数，那么从这个位置往后，从左到右，都必须有默认值。
//int func0(int a, int b = 10, int c ) {
//	int sum = a + b + c;
//	return sum;
//}
int func1(int a, int b = 10, int c = 100) {
	int sum = a + b + c;
	return sum;
}
//注意事项，如果函数的声明有默认值，函数的实现就不能有默认值。只能有其中一个有默认参数，不然就会产生二义值。
int func2(int a=10, int b = 20);

//int func2(int a = 10, int b = 20) {
//	int sum = a + b;
//	return sum;
//}

//函数重载：

int func2(int a, int b) {
	int sum = a + b;
	return sum;
}

int func2(int a) {
	int sum = a + 10;
	return sum;
}

int func2() {
	int sum = 10 + 10;
	return sum;
}

double func2(double a,double b) {
	double sum = a + b;
	return sum;
}

//引用作为重载的默认条件
void func3(int& a) {//局部变量，在代码区
	cout << "func3(int&a)调用" << endl;
}
void func3(const int& a) {//全局变量，在全局区
	cout << "func3(const int&a)调用" << endl;
}
//const int &a和int&a类型不同，重载可以实现

//2.函数重载遇到默认参数（有可能出现歧义，应该尽量避免）
void func4(int a,int b) {
	cout << "func（int a,int b = 10）的调用" << endl;
}

void func4(int a) {
	cout << "func（int a）的调用" << endl;
}
//这种情况就会出现二义性，会导致报错。



int main() {
	int a = 1, b = 2, c = 3;
	int sum = func(a, b, c);//形参没有初始化的情况下，必须填入全部形参才能正常调用函数。
	int sum1 = func1(a, 1010);
	cout << "sum = " << sum << endl;//形参有初始化的情况下，优先使用传入的形参的值，如果没有，就用初始化的值。
	cout << "sum1 = " << sum1 << endl;
	int sum2 = func2(a, 1010);
	cout << "sum2 = " << sum2 << endl;
	double a_d = 3.14, b_d = 3.14;
	cout << "sum2_d= " << func2(a_d, b_d);
	//func4();
	return 0;
}