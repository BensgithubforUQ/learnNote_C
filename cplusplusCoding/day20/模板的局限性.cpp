#include <iostream>
#include <string>
using namespace std;

//模板是有局限性的，
//比如
class Person {
public:
	string name;
	int age;	

	Person(string n, int a) {
		this->name = n;
		this->age = a;
	}
};

template <class T>
bool myCompare(T &a, T &b) {
	if (a == b) {
		return true;
	}
	else {
		return false;
	}
}
template<> bool myCompare(Person &p1, Person& p2) {//利用具体化的Person版本来实现代码，优先调用
	if (p1.name == p2.name&&p1.age == p2.age) {
		return true;
	}
	else {
		return false;
	}
}

void test01(){
	int a = 10, b = 20;
	bool result = myCompare(a, b);
	if (result) {
		cout << "yes" << endl;
	}
	else cout << "no" << endl;

}

void test02() {
	Person p1("tom", 10);
	Person p2("tom", 20);
	bool result = myCompare(p1, p2);
	if (result) {
		cout << "yes" << endl;
	}
	else cout << "no" << endl;
}


//int main() {
//	test01();
//	test02();//报错的原因是因为Person是自定义的数据类型，c++中没有写这种运算符重载，无法比较person的大小。
//
//	return 0;
//}