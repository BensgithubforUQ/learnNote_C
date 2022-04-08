#pragma once
#include <iostream>
#include <string>
#include "virtual_father.hpp"
using namespace std;

template<class T1, class T2, class T3 >//进行一个buff的叠
class abstractFather {
public:
	virtual void showInfo() = 0;
	T1 name;
	T2 age;
	T3 id;
	//纯虚析构:因为子类中开辟了堆区数据，释放父类指针的时候无法调用子类析构代码
	//因此需要虚析构或者纯虚析构
	//纯虚析构需要类中定义，类外实现
	abstractFather() {
		cout << "父类构造函数调用" << endl;
	}
	virtual~abstractFather() = 0;
};

template<class T1, class T2, class T3 >
abstractFather<T1, T2, T3 >::~abstractFather() {//类模板的纯虚析构函数的类外实现
	cout << "纯虚析构调用" << endl;
}