#include <iostream>
#include <string>
using namespace std;

class Person;

class Person {
	friend ostream& operator<< (ostream& cout, const Person& p);
	friend Person operator+(Person& p1, Person& p2);
	friend Person operator+(const Person& p1, int a);
	friend Person operator-(Person& p1, Person& p2);
	friend Person operator-(const Person& p1, int a);
public:
	//成员函数重载+号运算符
	//Person operator+ (Person &p1) {
	//	Person temp;
	//	temp.m_A = this->m_A + p1.m_A;
	//	temp.m_B = this->m_B + p1.m_B;
	//	return temp;
	//}
	Person(int a, int b) :m_A(a), m_B(b) {
	}
	Person() {//这个{}一定要写，不然就会无法生成具体的函数模板，在需要调用构造函数的时候就会报错
		//无法解析的外部符号

	}
	void getValue();
	Person& operator++();
	const Person& operator++(int); //后置递增用，int代表占位参数


private:
	int m_A;
	int m_B;
	int* m_C;
};

void Person::getValue() {
	cout << "m_A = " << m_A << endl;
	cout << "m_B = " << m_B << endl;
}

Person operator+(Person& p1, Person& p2) {//全局函数重载加法运算符
	Person temp;
	temp.m_A = p1.m_A + p2.m_A;
	temp.m_B = p1.m_B + p2.m_B;
	return temp;
}

Person operator+(const Person& p1, int a) {//全局函数重载加法运算符 	
									//运算符重载也可以发生函数重载
	Person temp;
	temp.m_A = p1.m_A + a;
	temp.m_B = p1.m_B + a;
	return temp;
}

Person operator-(Person& p1, Person& p2) {//全局函数重载减法运算符
	Person temp;
	temp.m_A = p1.m_A - p2.m_A;
	temp.m_B = p1.m_B - p2.m_B;
	return temp;
}

Person operator-(const Person& p1, int a) {//全局函数重载减法运算符 	
									//运算符重载也可以发生函数重载
	Person temp;
	temp.m_A = p1.m_A - a;
	temp.m_B = p1.m_B - a;
	return temp;
}

ostream& operator<< (ostream &cout,const Person &p) {
	//全局函数重载左移运算符
	//cout是ostream类型的对象，且只有一个，所以不能创建新的，直接传入地址就行了
	//一般不用成员函数来重载左移运算符
	//因为如果成员函数，写法为 ostream& operator<<(ostream&cout）
	//这种写法最终得到的是p << cout，不符合重载的需求
	cout << "m_A = " << p.m_A << " m_B = " << p.m_B;
	return cout;
}



Person& Person::operator++() {//返回地址的原因是因为：
	/*++p是记录加完之后的值，直接返回结果值，而为了实现++（++p）这种功能
	必须保证每次++的对象都是原来那个对象，只有用地址传递才能实现这一个功能
	值传递会导致第二次并没有用到初始的那个对象*/
	this->m_A++;
	this->m_B++;
	return *this;
}

 const Person& Person::operator++(int ) {//不能返回地址的原因，是因为：
	//后置递增，是先记录当前结果，然后++，然后返回记录的结果
	/*比如cout<<p++;我们打印的是p++之前的值，而不是p+1的值
	这意味着我们返回的是p的值，但是要实现++，所以利用地址++，然后返回原来的值*/
	Person const *temp = this;//用一个对象指针记录当前对象的值
	this->m_A++;
    this->m_B++;//利用this指针指向的当前对象的特性，修改当前对象的值、
	return  (*temp) - 1;//返回记录的值
}
 
void test_add_operator() {
	Person p_1(10, 10);
	Person p_2(1, 1);
	Person p_3 = p_1 + p_2;//已经重载了的加号运算符，简化版，本质调用就是正经调用函数。
	Person p_4 = p_1 + 10;
	p_3.getValue();
	p_4.getValue();
}
void test_leftMove_operator() {
	Person p_1(10, 11);
	cout << p_1<<endl; //全局函数重载左移运算符,验证
}

void test_upward_operator() {
	Person p_1(10, 11);
	Person p_2(10, 11);
	cout << (++p_1)++ << endl; //全局函数重载前置++,验证，预测打印
	//cout << (p_2++)++ << endl; //全局函数重载后置++,不能连加
	cout << (p_2++)<< endl; //全局函数重载后置++,
	cout << p_2 << endl; //全局函数重载后置++,验证
}
int main() {
	test_add_operator();

	test_leftMove_operator();
	cout << "++h,h++" << endl;
	test_upward_operator();
	

	//测试一下++的性质
	int a = 1;
	//cout << (a++)++ << endl;//(a++)++是不允许的，因为c++里a++返回的是一个常量
	cout << a++ << endl;;
	cout << (++a)++ << endl; //这个可以
	//cout << ++(a++) << endl; //这个又不可以
	cout << a << endl;
	system("pause");
	return 0;
}