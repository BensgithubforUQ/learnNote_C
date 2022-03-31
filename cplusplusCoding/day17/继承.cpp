#include <iostream>
#include <string>
using namespace std;

//father class 1
class Animal { //虚继承的虚基类
public:
	int m_Age;
};
//sheep
class Sheep :virtual public Animal { //用virtual，虚继承来处理菱形问题（子类继承了两个相同类型的数据，造成了资源浪费）
public:
	//用了虚继承之后，sheep类从animal类继承的m_age是一个vbptr，是一个virtual base pointer
	//这个虚基类指针指向的是一个virtual base table，这个虚基类表记录的是一个偏移量，通过这偏移量，
	//编译器就能找到唯一的一个地址，记录着菱形继承中第二代子类继承的数据
private:

};
//Camelus
class Camelus :virtual public Animal {
public:

private:

};

//son class
class Alpaca :public Sheep, public Camelus {

};

//菱形继承，alpaca同时继承了sheep和camelus的成员和成员函数
void test01() {
	Alpaca a1;
	a1.Sheep::m_Age = 28;
	a1.Camelus::m_Age = 18;
	cout << "年龄（sheep）" << a1.Alpaca::Sheep::Animal::m_Age << endl;
	cout << "年龄（camelus）" << a1.Alpaca::Camelus::Animal::m_Age << endl;
	cout << "年龄（Alpaca）" << a1.m_Age << endl;
	//cout << "年龄（camelus）" << a1.Alpaca::Camelus::Animal::m_Age << endl;
}

//
//int main() {
//	test01();
//	return 0;
//}