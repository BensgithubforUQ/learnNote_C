#ifndef TESTCLASS_H
#include <iostream>
using namespace std;

class Test {
public:
	~Test() {
		cout << "析构..." << endl;
	}

	Test() {
		x = 0, y = 0; //默认构造
	} 
	Test(int x1, int y1):x(x1),y(y1) {} //赋值构造
	Test(Test& t) {  //拷贝构造
		this->x = t.x, this->y = t.y; 
	}
	void operator=(Test& t) { //赋值
		this->x = t.x, this->y = t.y;
	}
	void printTest() {
		cout << "x: " << x << " y: " << y << endl; 
	}
	void changeTest(int change_x, int change_y) {
		x += change_x;
		y += change_y;
	}
protected:
private:
	int x;
	int y;
};
#endif // !TESTCLASS_H
