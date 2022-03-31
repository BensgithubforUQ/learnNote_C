#include <iostream>
#include <string>
using namespace std;

void swap0(int a, int b) {//值传递形参
	int temp = a;
	a = b;
	b = temp;
	cout << "值传递栈区打印： a=" << a << " b=" << b << endl;
}
void swap1(int* a, int* b) {//地址传递形参
	int temp = *a;
	*a = *b;
	*b = temp;
	cout << "地址传递栈区打印： a=" << *a << " b=" << *b << endl;
}

void swap2(int& c, int& d) {//引用传递形参
	int temp = d;
	d = c;
	c = temp;
	cout << "引用传递栈区打印： a=" << c << " b=" << d << endl;
}
int &test0() {
	int a = 10;//局部变量，存放在四区中的栈区
	return a;
}

int& test1() {//函数的调用可以作为左值
	static int a = 10;//改为全局区的静态变量，而不是栈区的局部变量
	return a;
}

void showValue(int& val) {
	val = 1000;
	cout << "输出引用的值,val=" << val << endl;
}

void showValue1(const int& val) {
	//val = 1000;//为了防止误操作，加上const，来避免修改不想修改的值
	cout << "输出引用的值,val=" << val << endl;
}

int main() {
	int a = 1, b = 2;
	swap0(a, b);
	cout << "值传递代码区打印： a=" << a << " b=" << b << endl;
	swap1(&a, &b);
	cout << "地址传递代码区打印： a=" << a << " b=" << b << endl;
	swap2(a, b);
	cout << "引用传递代码区打印： a=" << a << " b=" << b << endl;
	//这里发现一个问题，用地址传递形参，在函数里修改之后，再用引用传递形参，这种情况下并不能用引用修改形参的方式修改实参
	//但是如果注释掉上一个地址传递形参的操作，就可以用引用传递形参然后修改并且对实参产生影响。

	//尝试返回栈区中的局部变量的引用
	int &ref = test0();//获取返回值的引用
	cout << "尝试返回栈区中的局部变量的引用" << ref << endl;//乱码，栈区在调用完就被释放，不能用引用访问。
	int& ref1 = test1();//获取返回值的引用，函数的调用可以作为左值
	cout << "尝试返回全局区中的静态变量的引用" << ref1 << endl;
	test1() = 100;//函数的调用可以作为左值,因为返回的值是函数里静态变量的一个引用。
	//而ref1是a的别名，因此test1的返回值实际上是原名，函数调用直接作为左值，则相当于修改原名
	//因此原名的引用，别名ref1，再被读取输出的时候，也会打印出原名的值。
	cout << "函数的调用可以作为左值" << ref1 << endl;

	//引用的本质：
	//引用本质是一个指针常量 auto *const p = &a;
	//p不可变，意味着地址不可变，但是指向的地址解出来的值可变。
	//就像&a，地址不可变，但是这个引用的值是可以修改的，本质是别名，但是地址一样。就像一个指针常量。

	//常量引用 const int &a = b;
	int a1 = 10;
	//int& b = 10;//int &b是代码区的引用，不可引用非法的内存空间，而10就是不代码区的引用不可引用的内存空间的数据。
	const int& b0 = 10;//但是这样就可以，因为const修饰之后，b0也是（引用）全局区的了。
	const int& b1 = a1;

	//这里是为了重新解释const int&的作用，用处是在规定函数中不可修改哪些值，以免误操作。
	showValue(a1);
	cout << "输出引用的值,a1=" << a1 << endl;
	showValue1(a1);
	cout << "输出引用的值,a1=" << a1 << endl;
	return 0;
}