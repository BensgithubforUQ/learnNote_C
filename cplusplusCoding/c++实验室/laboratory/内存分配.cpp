#include<iostream>
using namespace std;

//内存管理篇
//new 和 malloc
//malloc free是c标准库的函数
//new delete 是c++的运算符

int test() {
	return 0;
}

class A {
protected:
	A() {}
	~A() {}
public:
	static A* create() { //用create来返回堆区的A
		return new A();
	}

	void destroy() {
		delete this;
	}
};

class B {
private:
	void* operator new(size_t t) {} //重载new和delete，然后放到private里面，就能阻止在堆区创建对象
	void operator delete(void* ptr) {}
public:
	B() {}
	~B(){}
};

class C {
public:
	C() {};
	virtual ~C() {};
private:
	char a;
};

int a1;
//int main() {
//	const int *b = &a1;
//	static int a;
//	int* num = (int*)malloc(sizeof(int) * 10); //堆区
//	int* p = new int(256);
//	int* arr = new int[5](); //括号里面不能写数字
//	for (int i = 0; i < 10; i++) *(num+i) = i;
//	cout << "static int a:" << a << " 地址" << (int)&a<<endl;
//	cout << "int a1:" << a1 << " 地址" << (int)&a1 << endl;
//	cout << "const int *b  :" << *b << " 地址" << (int)b << endl;
//	cout<<"num[9]:" << num[9] << " 地址" << (int)num<<endl;
//	cout << "int *p" << *p << " 地址 " << (int)p << endl;
//	cout << "abcde" << " 地址 " << (int)&("abcde") << endl;
//	free(num); 
//	delete p;
//
//	for (int i = 0; i < 5; i++) cout << arr[i] << " ";
//	delete[] arr;
//
//	C c;
//	cout << "sizeof c " << sizeof(c) << endl;//虚函数表，参与内存对齐
//	return 0;
//}