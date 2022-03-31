#include<iostream>
#include "Sales_item.h"
using namespace std;

//int main() {
//	cout << "enter two number:" << endl;
//	int v1 = 0, v2 = 0;
//	cin >> v1 >> v2;
//	cout << "the sum of " << v1 << " and " << v2 << " is " << v1 + v2 << endl;
//
//	return 1;
//}

//int main() {
//	int sum = 0, val = 1;
//	while (val <= 10) {
//		sum += val;
//		++val;
//		cout << sum << endl;
//	}
//	return 0;
//}

//int main() {
//	int val = 50, sum = 0;
//	while (val <= 100) {
//		sum += val;
//		++val;
//		cout << sum << endl;
//	}
//	return 0;
//}

//int main() {
//	int val = 10, sum = 0;
//	while (val >= 0) {
//		sum += val;
//		--val;
//		cout << sum << endl;
//	}
//	return 0;
//}

//int main() {
//	int firstN, lastN, val;
//	cin >> firstN >> lastN;
//	if (lastN <= firstN) {
//		int temp = 0;
//		temp = lastN;
//		lastN = firstN;
//		firstN = temp;
//	}
//	val = firstN;
//	while (val <= lastN) {
//		cout << val << endl;
//		val++;
//	}
//	return 0;
//}

//int main() {
//	int value, sum;
//	sum = 0;
//	while (cin >> value) {
//		sum += value;
//	}
//	cout << sum << endl;
//}
//输出完了之后要ctrl+d/z

//int main() {
//	int currval = 0, val = 0;
//	if (cin >> currval) {
//		int cnt = 1;
//		while (cin >> val) {
//			if (val == currval) {
//				++cnt;
//			}
//			else {
//				cout << currval << " occurs " << cnt << " times " << endl;
//				currval = val;
//				cnt = 1;
//			}
//		}
//		cout << currval << " occurs " << cnt << " times " << endl;
//		return 0;
//	}
//}

//int main() {
//	//bookNo(book), units_sold(0), revenue(0.0) { } 
//	Sales_item item1, item2;
//	cin >> item1 >> item2;
//	if (item1.isbn() == item2.isbn()) {
//		cout << item1 + item2 << endl;
//		return 0;
//	}
//	else cerr << "Data must refer to same ISBN" << endl;
//	return -1;
//	return 0;
//}

//string global_str;
//int global_int;
////内置类型的变量的初始化，如果在函数外，就默认初始化为零或者空，在函数内无法默认初始化，如果没有初始化就不能进行操作。
//int main() {
//	int input_value;
//	cin >>input_value;
//	int i{ 3};
//	cout << i << endl;
//	double wage;
//	double salary = wage = 9999.99;
//	cout << salary <<" " << wage << endl;
//	int j = 3.14;
//	cout << j<<endl;
//	cout << global_str << endl;
//	cout << global_int << endl;
//	return 0;
//}

//int i = 40;
//int main() {
//	double Double = 0.01;
//	int _ = 0;
//	cout << Double<<" "<<_<<endl;
//	int i = 42;
//	int j = i;
//	cout << i << " " << ::i << " " << j;
//	return 0;
//}

//int main() {
//	int i = 100, sum = 0;
//	for (int i = 1; i <= 10; i++) {
//		sum += i;
//	}
//	cout << "sum = " << sum;
//	return 0;
//}

//int main() {
//	int i = 0, &r1 = i;
//	double d = 0, &r2 = d;
//	r2 = 3.14;
//	i = r2;
//	i = 1;
//	r1 = 3;
//	cout << r2 << " " << d << endl;
//	cout << i << " "<<r1;
//	return 0;
//}