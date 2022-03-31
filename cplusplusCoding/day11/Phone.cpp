#include "Phone.h"

Phone::Phone(const Phone& p) {
	number = p.number;
	type = p.type;
	cout << "用拷贝构造函数初始化 号码： " << number << " 类型: " << type << endl;
}

Phone::Phone() {
	cout << "用无参构造函数初始化phone对象" << endl;
}


Phone::Phone(int n, string t) :number(n), type(t) {
	//用初始化列表初始化phone对象
	cout << " phone?"  << endl;
}

int Phone::getNum() {
	return number;
}
string Phone::getStr(){
	return type;
}
void Phone::showPhone() {
	cout << "对象的 号码： " << number << " 类型: " << type << endl;
}
Phone::~Phone() {
	cout << "调用析构函数清理phone类型的对象" << endl;
}