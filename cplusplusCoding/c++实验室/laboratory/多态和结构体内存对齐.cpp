#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
//#include "poly.h"
using namespace std;
//结构体和类的区别，多态，继承，虚函数
struct st1 { //结构体默认公有，c风格中不能含有成员函数
	int a; //4
	char b; //1
	short c; //2
	double d; //8
	long l; //4
	//(4+1+2+"1") + (8) + (4 +"4")
};

class Poly { //类默认私有，c++风格中可以包含成员函数
public:
	Poly() {};
	Poly(const Poly &p) { //拷贝构造不能用值传递，否则会陷入无限递归。
		this->a = p.a;
	}
	Poly(int x, char y, int *z) :a(x), b(y) ,c(z) {
	} //构造函数不能是虚函数，因为vtable在构造函数中初始化，而调用虚函数需要用vtable
	virtual ~Poly() {}; //发生多态的时候，需要降基类的析构函数定义为虚函数，否则无法执行派生类析构函数
	//虚函数也可以是内联函数，但是就不能用于多态了，因为虚函数多态是动态多态，在编译阶段无法进行，而内联需要在编译阶段替换。
	virtual void print_po() {}; //vtable也要参与对齐
private:
	int a = 1;
	char b = 'a';
	int* c;
};
//char ：1个字节
//short int : 2个字节
//int： 4个字节
//unsigned int : 4个字节
//float : 4个字节
//double : 8个字节
//long : 4个字节
//long long : 8个字节
//unsigned long : 4个字节

class Poly_son :public Poly {
	friend ostream& operator<<(ostream &out,const Poly_son &p); //vtable也要参与对齐
public:
	Poly_son() {};
	Poly_son(const Poly_son& p) { //拷贝构造不能用值传递，否则会陷入无限递归。
		this->a = p.a;
	}
	Poly_son(int x, char y, int* z,string s) :a(x), b(y), c(z) {
		this->str = s;
	} //构造函数不能是虚函数，因为vtable在构造函数中初始化，而调用虚函数需要用vtable
	~Poly_son() {}; //发生多态的时候，需要降基类的析构函数定义为虚函数，否则无法执行派生类析构函数
	
private:
	int a = 1;
	char b = 'a';
	int* c;
	string str;
};
ostream& operator<<(ostream& out, const Poly_son& p) {
	out << p.a << " " << p.b << " " << *(p.c) << " " << p.str << endl;
	return out;
}

int main() {
	st1 st_1;
	cout << " 结构体st1的size " << sizeof(st_1) << endl;
	Poly po;
	cout << " 有虚函数的类po的size " << sizeof(po) << endl;
	int n = 0;
	int* p = &n;
	int a = 2;
	char b = 'b';
	string s = "112";
	Poly_son po_s(n,b,p,s);
	cout << po_s << endl; //友元，重载<<，打印类的私有成员变量。
	cout << " 基类有虚函数的子类po_s的size " << sizeof(po_s) << endl;
	return 0;
}