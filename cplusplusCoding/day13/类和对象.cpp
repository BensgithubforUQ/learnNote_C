#include <iostream>
#include <string>
using namespace std;


/*常函数
成员函数后加const，我们就称之为常函数
常函数内不可以修改成员属性
成员属性声明的时候如果加了关键字mutable，就可以在常函数中修改了
*/

/*常对象
声明前加const就是常对象
常对象只能调用常函数
*/
class Person {
public:
	void showPerson() const{
		//this->m_a = 10;
		//this指针的本质是一个指针常量 即 const 类* this，再加个const
		//就是 const 类* const 类
		//这样就不能修改了
		cout << "m_a = " << m_a << endl;
		this->m_b = 10;//但是加个mutable就可以修改了
	}

	void funcNoConst() {

	}

	int m_a;
	mutable int  m_b;
};

int main() {
	//复习一下指针常量和常量指针
	int i = 1,j = 10;
	int* const a = &i;//常量指针
	cout << "a的地址：" << (int)&a << " 储存的地址： " << (int)a << " 指向的值： " << *a << endl;
	//a = 1;//指针a不可改
	//a = &j;
	int* A = &i;
	A = &j;
	*a = 2;//但是指针指向的变量可以改。
	cout << "a的地址：" << (int)&a << " 储存的地址： " << (int)a << " 指向的值： " << *a << endl;
	cout << i << endl;
	const int* b = a;//指针常量，不能通过这个指针修改指向的变量，但是可以通过其他方法改，而且改了之后
	//解常量指针指向的地址，还能发现，他指向的变量还改了、
	cout << "b的地址：" << (int)&b << " 储存的地址： " << (int)b << " 指向的值： " << *b << endl;
	//*b = *a; //这个指针指向的变量不能改，
	int c = 3;
	int *d = &c;
	b = d; //但是指针本身可以改
	cout << "b的地址：" << (int)&b << " 储存的地址： " << (int)b << " 指向的值： " << *b << endl;

	//常对象
	const Person p_const;
	//p_const.m_a = 10; //常对象只能调用常函数，不能修改变量。
	p_const.m_b = 10; //m_b加了mutable，常对象是可以访问修改的。
	p_const.showPerson();
	//p_const.funcNoConst();//常对象不能调用常函数以外的函数，因为以外的函数有可能访问属性。

	//double *arr = new double[2000000*12*12];
	//double*** array_3d = new double** [2000000];
	//for (int i = 0; i < 2000000; ++i) {
	//	array_3d[i] = new double* [12];
	//	for (int j = 0; j < 12; ++j) {
	//		array_3d[i][j] = new double[12];
	//		for (int k = 0; k < 12; ++k) {
	//			array_3d[i][j][k] = 1;
	//		}
	//	}
	//}
	system("pause");
	return 0;
}