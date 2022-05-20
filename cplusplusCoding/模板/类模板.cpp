#include <iostream>
#include <string>
using namespace std;

//类模板
template<class nameType, class AgeType = int>//类模板在模板参数列表中可以有默认参数，函数模板中不允许
class People {
public:
	nameType m_name;
	AgeType m_age;
	//类模板中的成员函数的创建时机
	//在普通类中，成员函数可以在一开始就创建
	//在类模板中，成员函数在被调用的时候才创建,记住就行了	
	void showPerson() {
		cout << this->m_name << " " << this->m_age << endl;
	}

	People(nameType name, AgeType age) {
		this->m_name = name;
		this->m_age = age;
	}
};
/*类模板对象做函数参数*/
//1.指定传入类型-直接显示对象的数据类型*******最重要，最常用，最直接。
void printPerson1(People<string>& p) {//类模板在模板参数列表中可以有默认参数，函数模板中不允许,可以不写int
	p.showPerson();
}
//2.参数模板化-将对象中的参数变为模板进行传递
template<class nameType, class AgeType>//提供模板
void printPerson2(People<nameType, AgeType>& p) {//参数模板化
	p.showPerson();
	cout << typeid(nameType).name() << endl;//可以通过这种方式知道，模板中自动推导出什么类型。
	cout << typeid(AgeType).name() << endl;
}
//3.整个类模板化-将这个对象类型模板化进行传递
template<class T>//提供模板
void printPerson3(T &p) {
	p.showPerson();
	cout << typeid(T).name() << endl;
	//class People<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,int>
	//得到的是这个类名，可以看到是一个class <string,int> 的类
}
//类模板和函数模板的区别
/*
1.类模板，没有自动类型推导的方式，需要指定
2.类模板在模板参数列表中可以有默认参数
*/
//int main() {
//	People <string, int> p1("张三", 30);//类模板，没有自动类型推导的方式，需要显示指定类型<string, int>
//	//p1.showPerson();
//	//People <string> p2("李四", 30);//类模板在模板参数列表中可以有默认参数，已经定义了int，因此这个地方可以这样用
//	//p2.showPerson();
//	printPerson1(p1);
//	printPerson2(p1);
//	printPerson3(p1);
//	return 0;
//}