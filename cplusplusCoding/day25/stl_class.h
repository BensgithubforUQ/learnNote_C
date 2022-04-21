#pragma once
#include <iostream>
#include <string>
using namespace std;

//函数对象
/*stl函数对象
重载操纵调用操作符的类，本质是个类，其对象称为函数对象
但是使用的时候很像函数，所以叫仿函数*/
/*
1.可以有参数，可以有返回值，
2.超出普通函数的概念，可以拥有自己的状态
3.函数对象可以作为参数进行传递
*/
class myAdd {
public:
	int operator()(int v1, int v2);
};

int myAdd::operator()(int v1, int v2) {
	return v1 + v2;//可以有返回值，可以有参数
}

void test0() {
	myAdd my_add;
	cout << my_add(10, 32) << endl;//像一个函数一样调用，有参数，也有返回值
}

class myPrint {//可以有自己的状态
public:
	myPrint() {
		this->count = 0;
	}
	void operator()(string s1);
	//可以设置一个值，来记录这个函数调用了多少次
	int count;
};

void myPrint::operator()(string s1) {
	this->count++;
	cout << s1 << endl;
}

void test1() {
	myPrint my_Print;
	my_Print("test");//像一个函数一样调用，有参数，也有返回值
	my_Print("test");
	my_Print("test");
	my_Print("test");
	
}

void doPrint(myPrint &p,string test) {
	p(test);
	cout << "my_Print调用了：" << p.count << "次" << endl;
}


void test2() {//3.函数对象可以作为参数进行传递
	myPrint my_Print;
	for (int i = 0; i < 5; i++) {
		doPrint(my_Print, "hello world");
	}
	//复习一下，引用传参，是实参，不是形参。
}