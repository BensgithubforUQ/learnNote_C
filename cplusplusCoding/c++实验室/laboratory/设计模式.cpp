#pragma warning(disable:4996)
#include<iostream>
#include <windows.h>
#include<thread>
#include"factory.hpp"
#include"abstractFactory.hpp"
#include "singleton.hpp"
#include "poly.h"
using namespace std;

void test_factory() {
	//工厂模式
	Factory* fac = new ConcreteFactory();
	Product* pro = fac->CreateProduct();
	
	delete fac;
	delete pro;
	//经过测试，发现factory和product除了是用工厂类调用create产品类以外，没有关系，析构顺序不相关。
	//工厂模式的优势在于，构造工厂类，然后调用createXXX方法(该方法里面封装了new XXX的操作)，不用在意XXX的参数和名字
	//缺点在于，对于XXX和YYY产品，需要构造一个新的XXX工厂类或者新的YYY工厂类，然后要创建还要先new该工厂类这就是麻烦的点了。
	//关键：会造成类爆炸。
}

void test_abstract_factory() {
	//抽象工厂模式
	//factory模式实现new多种factory，然后factory具体类中实现多product类的对象的创建，在一个工厂里聚合多个产品。
	AbstractFactory* ab_fac = nullptr;
	ab_fac = new ChineseFactory;
	AbstractApple *apple =  ab_fac->createApple();
	AbstractBanana* banana = ab_fac->createBanana();

	apple->showName();
	banana->showName();

	delete banana;
	delete apple;
	delete ab_fac;
	//优点，解决了类爆炸的问题。
	//缺点，解决类爆炸的方法很屮，在扩展产品族的时候，需要在工厂类的基类和子类里面添加方法。扩展难。
}

SingletonLazy* test_threadSafe() {
	return SingletonLazy::getInstance();
}

void test_SingletonsLazy() {
	Sleep(1000);
	if (SingletonLazy::getCount()) cout << "已创建对象..." << endl;
	else cout << "还未创建对象..." << endl;
	thread th_1(test_threadSafe);
	Sleep(1000);
	SingletonLazy* sl1 = test_threadSafe();
	SingletonLazy* sl2 = test_threadSafe();
	Sleep(1000);
	if (SingletonLazy::getCount()) cout << "已创建对象..." << endl;
	else cout << "还未创建对象..." << endl;
	if (sl1 == sl2) cout << "同一个" << endl;
	th_1.detach();

}

void test_SingletonHungry() {
	SingletonHungry* sh1 = SingletonHungry::getinstance();
	SingletonHungry* sh2 = SingletonHungry::getinstance();
	if (sh1 == sh2) cout << "同一个" << endl;
	cout << (int)sh1 << endl;
	sh1->freeSpace();
	sh2->freeSpace();
	cout << (int)sh2 << endl;
	SingletonHungry* sh3 = SingletonHungry::getinstance();
	//SingletonHungry::freeSpace();
}

void test_poly() {
	Poly_grandson gs;
	Poly g;
	Poly_daughter d;
	Poly_son s;

	cout << sizeof(gs) << " ";
	cout << sizeof(g) << " ";
	cout << sizeof(d) << " ";
	cout << sizeof(s) << " ";
}

void test_strcpy(char * c) {
	//c = (char*)malloc(100);
	int i;
	char str[10], str1[10];
	if (strlen(c) <= 10) strcpy(str, c);
	cout << strlen(c) << endl;
}



/*int main() {
	//test_SingletonHungry();
	//test_SingletonsLazy();
	//char* p = nullptr;
	//test_strcpy(p);
	//if(p!=nullptr) strcpy(p, "abcdedf");
	//printf("%s\n", p);
	

	//int a = 15, b = 26; //括号表达式
	//cout << (a, b) << endl;

	//   C++把"cout << 字符型指针"这种输出格式安排给输出字符串了，
	// 就是说它被编译器解释为从指针开始一个接一个地输出内存单元里的字符，
	// 直到遇到'\0'时为止。要想输出地址你强制成别的类型就可以了：如cout << (void *)&c << endl;就可以.
	//char c[] = {'0','1','2','3','\0'};
	//char* const p1 = c + 1;
	////char* c1 = "0123456789";
	//cout << *p1 << endl;
	//char d = 'n';
	////d = *p1;
	//cout << (void*) & d << endl;
	//test_strcpy(c);

	//vector<char>和string
	//string s1 = "123456789";
	//s1 += '\0';
	//s1 += '0';
	//cout << s1.back() << " " << s1.size() << endl;
	//vector<char> s2{ '1','2','3','4','5','6','7','8','9','\0' };
	//s2.push_back('\0');
	////s2.push_back('0');
	//cout << s2.back() << " " << s2.size() << endl;

	unique_ptr<int> u_ptr = make_unique<int>(114514);
	cout << *u_ptr << endl;
	
	return 0;
}*/