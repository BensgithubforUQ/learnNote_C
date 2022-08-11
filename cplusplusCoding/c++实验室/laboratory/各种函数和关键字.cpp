#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define MAX(a,b) ((a)>(b) ? (a) : (b))
inline int MAX_inline(int a, int b) {
	return a > b ? a : b;
}
//lambda表达式
void sortLambda(vector<int>& v) {
	sort(v.begin(), v.end(), [](int a, int b) {return a < b; });
}

//重载字符串
ostream& operator<<(ostream& out, vector<int>& v) {
	for (auto i : v) out << i << " ";
	out << endl;
	return out;
}

class A { //类中的成员函数都默认是inline函数
public:
	//关键字 explicit
	//explicit A(int x) { //禁止隐式转换，就是禁止编译器自己给你转换形态
		//val = x;
	//}
	A(int x,int y):const_i(y) { //禁止隐式转换，就是禁止编译器自己给你转换形态
		val = x;
 		count++;
	}

	~A() {
		count--;
	}

	static int getCount() { return count; } //static 静态成员函数不能调用非静态成员函数或者非静态成员变量
	//因为里面没有this指针

	int getI() const { //const成员函数只能访问const类型的成员函数或者变量
		//cout << const_i << endl;
		return const_i;
	}
private:
	static int count; //静态成员变量是所有同类对象维护了一个相同的值
	int val;
	const int const_i;
};

int A::count = 0;

//关键字static
int fun() {
	static int val = 1; //只在第一次调用该函数的时候初始化
	val+=1;
	return val;
}

//int main() {
//	vector<int> v{ 1,4,2,6,3,2,5,7 };
//	cout <<"lambda函数排序之前 " << v << endl;
//	sortLambda(v);
//	cout <<"lambda函数排序之后 " << v << endl;
//
//	cout << "MAX宏： " << MAX(v[0], v[1]) << endl;
//	cout << "MAX_inlne函数： " <<MAX_inline(v[0], v[1]) << endl;
//
//	//带static静态成员变量的类，可以使得同类对象共享静态成员变量的值，使类和静态成员变量相关
//	A a (10,10);
//	A a1  (10,20);
//	A* a3 = new A(10,30);
//	cout << "获得类A的static 变量 count的值： " << A::getCount() << endl;
//	cout << "获得类A的const 变量 const_i的值： " << a1.getI() << endl; //20
//	delete a3; //释放a3的类
//	cout << "获得类A的static 变量 count的值： " << A::getCount() << endl;
//
//
//	//static关键字修饰的变量在函数第一次调用的初始化。
//	cout << "fun函数打印，static变量在函数第一次被调用的时候初始化" << endl;
//	for (int i = 0; i < 3; i++) cout << fun() << " "; // 2 3 4
//	
//	return 0;
//}