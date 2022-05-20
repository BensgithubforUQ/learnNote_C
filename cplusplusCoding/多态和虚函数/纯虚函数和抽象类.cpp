#include <iostream>
#include <string>
using namespace std;
//纯虚函数和抽象类
class Base {//只要一个类有一个纯虚函数，那就是抽象类
	/*抽象类特点
	1.抽象类无法实例化对象
	2.抽象类的子类，必须重写父类中的纯虚函数，否则也属于抽象类*/
public:
	virtual void func() = 0;//纯虚函数
};

class Son : public Base {//继承父类base，base是抽象类，但是son里面没重写纯虚函数
	//因此也是抽象类
public:
};
class Son_x :public Base {//重写了父类中的虚函数
public:
	void func() {
		cout << "func的调用（son_x)" << endl;
	}
};
//int main() {
//	//Base b_test;
//	//Son s_test;
//	Base* s_x = new Son_x;
//	s_x->func();
//	return 0;
//}