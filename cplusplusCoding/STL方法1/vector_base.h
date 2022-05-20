#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>

using namespace std;

void constructVectorWithSize(vector<int> &v,int size) {//初始化一个有size个元素的vector容器
	//srand((unsigned int)time(NULL));
	if (v.empty() && size != 0) {
		for (int i = 0; i < size; i++) {
			v.push_back(rand() % 10 + 1);
		}
	}
}

void printInt_function(int n) {//用于for_each的打印函数名
	cout << n << " ";
}



class PrintInt_functor {
public:
	void operator()(int n) {
		cout << n << " ";
	}
};

class Transform {
public:
	int operator()(int n) {
		return n + 1;
	}
};

void printVector(const vector<int> v) {
	if (!v.empty()) {
		for (auto it = v.begin(); it != v.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	else {
		cerr << "blank vector" << endl;
	}
}

