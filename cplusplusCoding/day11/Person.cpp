#include "Person.h"


Person::Person() {
	cout << "用无参构造函数初始化对象" << endl;
}
//Person::Person(int a,int h) {//有参构造函数，在用初始化列表之后就不用这套了
//	age = a;
//	m_height = new int(h);//在向堆区中传递数据
//
//	cout << "用有参构造函数初始化对象" << endl;
//}
Person::Person(const Person& p) {//浅拷贝（编译器自带的拷贝构造函数也是浅拷贝 ）
	//在遇到堆区数据的时候，如果使用下面的析构函数主动释放堆区内存
	age = p.age;//则会因为栈区先进后出的原则，优先释放了被初始化的对象的堆区内存
	//m_height = p.m_height;//而用浅拷贝本身就是逐字节的拷贝，因此在后释放用于初始化别的对象的原对象的时候
	//会发生重复操作，即原对象的堆区内存已经被释放了，不可以再次释放，这就是一种非法操作。
	//为了解决这个问题，就需要用到深拷贝。
	//所谓深拷贝，就是在初始化的时候，重新申请一个堆区内存用处储存新对象的数据。
	//这样就不会再释放的时候导致重复和交叉堆区释放。
	m_height = new int(*p.m_height);
	//这里就是用new int重新开辟了一块堆区内存，然后把p用*解地址，并且把该对象的身高属性传入到新开辟的堆区内存里面
	//这样就可以把两个对象的堆区内存分开，而不是公用同一个。
	//这就是深拷贝
	p_Phone = p.p_Phone;
	cout << "用拷贝构造函数初始化对象" << endl;
}
Person::~Person() {//析构函数，通常用于将堆区开辟的数据释放。
	if (*m_height != NULL) {
		delete m_height;
		m_height = NULL;
	}
	cout << "用析构函数清理对象" << endl;
}

int Person::getAge() {
	return age;
}

int Person::getHeight() {
	return *m_height;
}

Person::Person(int a, int h,Phone p_0) :age(a), m_height(new int(h)), p_Phone(p_0) {
	cout << "person？" << endl;
}
void Person::showP() {
	p_Phone.showPhone();
}
	//private:
//	int age;
//int* m_height;//身高，用指针是因为想要在堆区储存这个数据

