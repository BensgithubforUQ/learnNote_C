#pragma once
#include <functional>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
逻辑仿函数
template <class T> bool logical_and<T> //逻辑与
template <class T> bool logical_or<T> //逻辑或
template <class T> bool logical_not<T> //逻辑非
*/

/*逻辑仿函数在开发中基本上用不上*/
void prindVector(vector<bool> &v) {
	if (v.empty()) {
		cerr << "blank" << endl;
	}
	else {
		for (vector<bool>::iterator it = v.begin(); it != v.end(); it++) {
			if (*it) {
				cout << "true" << " ";
			}
			else {
				cout << "false" << " ";
			}
		}
		cout << endl;
	}
}

void test_logical_not() {
	//logical_not
	vector<bool> v;
	v.push_back(true);
	v.push_back(true);
	v.push_back(true);
	v.push_back(true);
	v.push_back(false);
	v.push_back(false);
	
	prindVector(v);
	vector<bool>v2;
	v2.resize(v.size());//要用搬运算法，必须提前开辟空间，因此要用到resize
	//用逻辑非仿函数，把v1中的元素取反，然后放到v2中
	transform(v.begin(), v.end(), v2.begin(), logical_not<bool>());
	prindVector(v2);
}