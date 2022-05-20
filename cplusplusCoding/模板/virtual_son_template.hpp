#pragma once
#include "virtual_father.hpp"


template<class T1, class T2, class T3 ,class T4>
class son_template_father:public abstractFather<T1,T2,T3> {//子类，类模板，声明
	//类模板与全局函数与友元
	/*类内实现友元全局函数*/
	friend void printThisClassInfo(son_template_father<T1, T2, T3, T4> &s) {
		cout << s.name << " " << s.age << " " << s.id << " " << *(s.address) << endl;
	}//也可以写在类外，需要提前让编译器知道此类和此函数的存在，都写在此类之前。
	//建议类内实现，类外实现过于复杂，并且容易出错
	//因为这是个全局函数，类外实现的是个函数模板，不是一个东西。

public:
	void showInfo();
	son_template_father(T1 n, T2 a, T3 i, T4 add);
	~son_template_father();
private:
	T4 *address;
};

template<class T1, class T2, class T3, class T4>
void son_template_father<T1, T2, T3, T4>::showInfo() {
	cout << this->name << endl;
	cout << this->age << endl;
	cout << this->id << endl;
	cout << *(this->address) << endl;
}

template<class T1, class T2, class T3, class T4>
son_template_father<T1, T2, T3, T4>::son_template_father(T1 n, T2 a, T3 i, T4 add) {
	this->name = n;
	this->age = a;
	this->address = new T4(add);
	this->id = i;
	/*cout << typeid(T1).name() << endl;
	cout << typeid(T2).name() << endl;
	cout << typeid(T3).name() << endl;
	cout << typeid(T4).name() << endl;*/
	cout << "构造函数调用" << endl;
}

template<class T1, class T2, class T3, class T4>
son_template_father<T1, T2, T3, T4>::~son_template_father() {
	if (this->address != NULL) {
		delete this->address;
		this->address = NULL;
		cout << "address的虚析构" << endl;
	}

}