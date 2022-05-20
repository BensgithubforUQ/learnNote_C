#include <iostream>
#include <string>
using namespace std;
//虚析构和纯虚析构
/*如果子类中有属性开辟了堆区内存，那父类指针在释放的时候无法调用到子类的析构代码，
因此需要在父类中写虚析构和纯虚析构*/
//用多态的时候，子类需要在堆区开辟内存，在父类指针释放的时候就无法直接调用子类的析构代码
//这时候就要把父类的析构函数写成虚析构函数或者纯虚析构函数，这样就能调用子类的析构函数
//如果用虚析构，那父类还可能可以实例化
//如果使用纯虚析构，那父类也变成了抽象类，不能实例化（抽象类：有纯虚函数的类。不可实例化。
class Animal1 {
public:
	Animal1() {
		cout << "animal1的构造" << endl;
	}
	virtual void speak() = 0;
	
	//virtual ~Animal1() {//虚析构
	//	cout << "animal1的析构" << endl;
	//}
	virtual ~Animal1() = 0;//纯虚析构也可以解决这个问题，但是必须有函数体实现，写在抽象类外
	//并且有了纯虚析构之后，该类也就是抽象类了，无法实例化对象。
};
Animal1::~Animal1() {//纯虚析构的函数实现
	cout << "animal1的纯虚析构" << endl;
}

class Cat1 :public Animal1{
public:
	Cat1(string name) {
		cout << "构造cat" << endl;
		c_name = new string(name);
	}
	void speak() {
		cout << "cat "<<*c_name<<" speaks" << endl;
	}
	~Cat1() {
		if (c_name != NULL) {
			cout << "析构cat" << endl;
			delete c_name;
			c_name = NULL;
		}
	}

private:
	string* c_name;
};

void test10() {
	Animal1* a = new Cat1("tom");//父类指针在析构的时候，不会调用子类的析构函数
	//因此如果子类如果有在堆区的属性，就会无法析构，会导致内存泄漏
	//解决方法是把析构改成虚析构
	a->speak();
	delete a;
}
//
//int main() {
//	test10();
//	return 0;
//}