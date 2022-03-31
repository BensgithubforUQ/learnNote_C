#include "person.h"

void test0() {
	Phone phone_0(45591901, "诺基亚");
	Phone phone_1(phone_0);
	Person p1(18, 150,phone_0);//用有参构造函数初始化对象p1,并且赋值18
	cout << "p1的年龄为：" << p1.getAge() << "身高为： " << p1.getHeight() << endl;
	p1.showP();
	Person p2(p1);//利用拷贝构造函数拷贝一个p1
	cout << "p2的年龄为：" << p2.getAge() << "身高为： " << p2.getHeight() << endl;
	p2.showP();
}

