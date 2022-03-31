#include <iostream>
#include <string>
using namespace std;
//c++面向对象三大特性，封装，继承，多态。
//多态：
/*静态多态：函数重载和运算符重载，就是静态多态，是函数名的复用
而c++中一般说的多态，都是动态多态，用派生类和虚函数来运行实时多态*/

//对于静态多态来说，在编译阶段就能确定函数地址
//而对于动态多态来说，在运行阶段才能确定函数地址
//动态多态的满足条件
/*1.有继承关系
2.子类重写父类的虚函数 
//函数返回值的类型，函数名，函数的参数列表，完全相同，就是重写，但是可以不加virtual。
动态多态的使用：
父类的指针或者引用，来指向子类的对象*/
class Animal {
public:
	virtual void speak();//如果想让狗说话，就需要把函数地址进行晚绑定，需要在运行阶段绑定。
	//这就要用到动态多态,定义一个虚函数

};
void Animal::speak() {
	cout << "animal叫" << endl;
}

class Cat :public Animal {
public:
	void  speak(); //如果想让猫说话，就需要把函数地址进行晚绑定，需要在运行阶段绑定。
	//这就要用到动态多态,定义一个虚函数
	//这里就是在子类中重写父函数的虚函数，是动态多态
	
};
void Cat::speak() {
	cout << "cat叫" << endl;
}

class Dog :public Animal {
public:
	 void  speak() {
		cout << "Dog叫" << endl;
	} 
};

//父类的（指针或者）引用，来指向子类的对象，来实现动态多态。
void test01(Animal& animal) {//注意c++中允许父类和子类之间的转换，不需要强制转换。
	//这里相当于 Animal &animal  = Cat;
	//这种情况下就是地址早绑定，是在编译阶段就确定了函数地址，因此最后输出的时候是调用的animal的speak。
	animal.speak();
}

void test02(Animal& animal) {//注意c++中允许父类和子类之间的转换，不需要强制转换。
	//如果想让猫说话，就需要把函数地址进行晚绑定，需要在运行阶段绑定。
	//这就要用到动态多态
	animal.speak();
}

//int main() {
//	Cat c1;
//	Dog d1;
//	test01(c1);//注意，将父类的speak改成虚函数之前，这里输出的会是动物叫
//	test02(d1);//注意，将父类的speak改成虚函数之前，这里输出的会是动物叫
//	system("pause");
//	return 0;
//}