#include <iostream>
using namespace std;

class father { //基类
public:
	father() {}
	virtual void print() = 0;
	virtual ~father() {}
};
//继承一下
class son : public father { //子类
public:
	son() {}; //无参构造 
	son(int _a, char _b, char *_str) :a(_a), b(_b) { 
		str = new char(*_str); //深拷贝
	} //有参构造函数
	son(const son& s) { //重载的拷贝构造
		this->a = s.a;
		this->b = s.b;
		this->str = new char(*s.str); //深拷贝
	}

	son& operator=(son& s) { //重载的赋值构造
		if (str != NULL) {
			delete str;
			str = NULL;
		}
		str = new char(*s.str); //深拷贝
		this->a = s.a;
		this->b = s.b;
		return *this;
	}

	~son(){
		delete str;
		str = NULL;
		cout << "释放了str指针维护的堆区数据" << endl;
	}

	void print() { //重写father类中的print函数
		cout << a << " " << b << " " << *str << endl;
	}

	void print(int x) { //隐藏father类中的print函数，同时是本类中print的重载
		cout << a << " " << b << " " << str << " 隐藏 " << endl;
	}
private:
	int  a;
	char b;
	char* str;
};

//int main() {
//	char str[] = "abcdedf";
//	int a = 1;
//	son s(a, 'b', str);
//	cout << sizeof(s) << endl;
//	son s1 = s;
//	s1.print(1);
//	return 0;
//}