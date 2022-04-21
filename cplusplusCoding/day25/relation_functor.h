#pragma once
#include <functional>
#include <iostream>
#include "predicate.h"
using namespace std;

/*关系仿函数
* template<class T> bool equal_to<T>;//等于
* template<class T> bool not_equal_to<T>;//不等于
* template<class T> bool greater<T>;//大于
* template<class T> bool greater_equal<T>;//大于等于
* template<class T> bool less<T>;//小于
* template<class T> bool less_equal<T>;//小于等于

*/

//降序，二元谓词,在predicate里面定义过了，这里直接用
//class descending {
//	bool operator()(int n1, int n2) {
//		return n1 > n2;
//	}
//};

void printVector(vector<int>&v) {
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

void test_greater() {
	vector<int> v;
	v.push_back(19);
	v.push_back(29);
	v.push_back(13);
	v.push_back(9);
	v.push_back(1);
	//打印
	printVector(v);
	//sort(v.begin(), v.end(), descending());//这里也可以不用自己写
	sort(v.begin(), v.end(), greater<int>());//用stl内建的函数对象，大于关系仿函数
	printVector(v);
}