#include <iostream>
#include <string>
#include "myHead.h"
using namespace std;

//int main() {
//	int num1 = 1,num2 = 2,num3 =3,num4 = 4;
//	int* p1 = &num1; //指针，可以改地址（p），也可以改指向的值（*p）。
//	const int* p2 = &num2;//常量指针（不可以改（*p），可以改p储存的地址
//	int* const p3 = &num3;//指针常量（不可以改p储存的地址，可以改p指向的值）
//	const int* const p4 = &num4;
//	
//	
//	//指针，可以改地址（p），也可以改指向的值（*p）。
//	cout << p1 << " " << *p1 << endl;
//	p1 = &num2;
//	*p1 = num1;
//	cout << p1 << " " << *p1 << endl;
//	cout << endl;
//	//常量指针（不可以改（*p），可以改p储存的地址
//	cout << p2 << " " << *p2 << endl;
//	p2 = &num3;
//	//*p2 = num3;
//	cout << p2 << " " << *p2 << endl;
//	cout << endl;
//	//指针常量（不可以改p储存的地址，可以改p指向的值）
//	cout << p3 << " " << *p3 << endl;
//	*p3 = num4;
//	//p3 = num4;
//	cout << p3 << " " << *p3 << endl;
//	cout << endl;
//
//	//什么都不能改
//	cout <<" p1" << p1 << " " << *p1 << endl;
//	cout << " p1" << p2 << " " << *p2 << endl;
//	cout << " p1" << p3 << " " << *p3 << endl;
//	cout << " p1" << p4 << " " << *p4 << endl;
//	cout << num1 << " " << num2 << " " << num3 << " " << num4 << endl;
//	swap(num1, num3);
//	cout << num1 << " " << num2 << " " << num3 << " " << num4 << endl;
//	int temp1 = add(num2, num3);
//	swap(temp1, num1);
//	cout << num1 << " " << num2 << " " << num3 << " " << num4 << endl;
//
//	return 0;
//}