#include <iostream>
#include <string>
using namespace std;
/*当子类继承的父类是一个类模板的时候
子类声明的时候，需要指定父类中T的类型
否则，编译器无法给子类分配内存
如果需要灵活的指定父类中T的类型，子类也应该是一个类模板*/
template<class T>
class Base {
public:
	T m;
};

class Son :public Base<int> {//子类声明的时候，需要指定父类中T的类型
	//否则，编译器无法给子类分配内存
};
template<class T1,class T2, class T3>
class Son_template :public Base<T2> {//如果需要灵活的指定父类中T的类型，子类也应该是一个类模板
public:
	T1 n;
	Son_template(T1 x, T2 y, T3 z);
	//类模板中成员函数的类外实现
	void showMember();
private:
	T3 l;
};
template<class T1, class T2, class T3>
void Son_template<T1,T2,T3>::showMember() {
	cout << this->n << " " << this->m << " " << this->l << endl;
}
//类模板的构造函数的类外实现
template<class T1, class T2, class T3>
Son_template<T1, T2, T3>::Son_template(T1 x, T2 y, T3 z) {
	this->n = x;
	this->m = y;
	this->l = z;
	cout << typeid(T1).name() << endl;
	cout << typeid(T2).name() << endl;
	cout << typeid(T3).name() << endl;

}



//
//int main() {
//	Son s1;
//	s1.m = 10;
//	cout << typeid(s1.m).name() << endl;
//	cout << s1.m << endl;
//
//	Son_template<int, char, int> s2('Y', 90 ,20);
//
//	s2.showMember();//因为指定的T1是int，而T1是n的类型，因此这里传入Y，就发生隐式类型转换
//	//因此打印n的值，出来的是ASCII码89，同理打印m，出来的是90对应的值，是Z
//
//    return 0;
//}