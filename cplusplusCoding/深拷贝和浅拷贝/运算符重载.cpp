#include <iostream>
#include <string>
using namespace std;

//整个运算符重载 = 赋值运算符 
class Person {
	friend void test01();
public:
	//构造函数

	Person() {//默认的构造函数

	}

	Person(int a,int b) {
		m_A = new int(a);//用指针m_A维护堆区的a的值，这里因为浅拷贝的原因，会导致堆区内存重复释放。
		m_B = b;
	}

	~Person() {
		delete m_A;
		m_A = NULL;
		cout << "释放m_A维护的堆区数据" << endl;//这里涉及深拷贝，如果用浅拷贝，在赋值运算之后
		//就会出现在析构用来赋值对象的时候，同时delete了被赋值的对象指向的堆区内存，就会报错。
		//堆区内存重复释放。
	}

	Person& operator=(Person &p) {//返回引用
		//编译器提供的是浅拷贝m_A = p.m_A;//指针相等，本质是传递地址
		//应该先判断，是否堆区有数据，如果有先释放，然后深拷贝
		if (m_A != NULL) {
			delete m_A;
			m_A = NULL;
		}
		//深拷贝
		m_A = new int(*p.m_A);//m_A是地址，*p.m_A是值，new int是地址。意思是在堆区开辟一个地址，存放值，然后把地址赋值给m_A;
		//对于非引用和指针的值，用浅拷贝就行了
		m_B = p.m_B;
		return *this;//this就是自身，解引用就是拿到自身这个对象
	}

	//重载==
	bool operator==(Person &p) {//!=和其他几个也都是一样的
		if ((*this->m_A == *p.m_A) && (this->m_B == p.m_B)) {
			return true;
		}
		else return false;
	}
private:
	int* m_A;
	int m_B;
};

void test01() {
	Person p1(1,1);
	Person p2,p3;
	p3 = p2 = p1;
	cout << *p3.m_A << endl;
	cout << p3.m_B << endl;
}

void test02() {
	Person p1(1, 1);
	Person p2(2, 1);
	if (p1 == p2) {
		cout << "yes" << endl;
	}
	else cout << "No" << endl;
}

int main() {
	//test01();
	test02();
	return 0;
}