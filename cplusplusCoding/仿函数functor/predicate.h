#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <algorithm>
using namespace std;

/*返回类型为bool的仿函数成为谓词
operator()接受一个参数称为一元谓词
operator()接受两个参数称为二元谓词*/

void printVector(const vector<int>& v) {
	for (vector<int>::const_iterator it = v.begin(); it != v.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}
class greaterFive { //一元谓词
public:
	bool operator()(int n) {
		return n > 5;
	}
};

void predicate0() {
	vector<int>v1;
	srand((unsigned int)time(NULL));
	int temp = 0;
	for (int i = 0; i < 10; i++) {
		temp = rand() % 10 + 1;
			v1.push_back(temp);
	}

	//查找又没大于5的数字
	//find_if(v1.begin(), v1.end(), greaterFive());//greaterFive()匿名的函数对象
	//返回的是第一个符合谓词返回值的迭代器
	vector<int>::iterator it = find_if(v1.begin(), v1.end(), greaterFive());
	if (it == v1.end()) {
		cout << "不含大于5的元素" << endl;
	}
	else {
		cout <<"第" << it - v1.begin() << "个数为:"<<v1[it - v1.begin()]<<", 值大于5" << endl;
	}
}


class descending { //二元谓词
public:
	bool operator()(int n, int m) {
		return n > m;
	}
};


void predicate1() {
	vector<int>v1;
	srand((unsigned int)time(NULL));
	int temp = 0;
	for (int i = 0; i < 10; i++) {
		temp = rand() % 10 + 1;
		v1.push_back(temp);
	}
	//排序
	sort(v1.begin(), v1.end(), descending());//升序,二元谓词使用方法，用二元谓词改变算法逻辑
	//注意，在对于会自动排序的数stl容器的时候，需要在声明和定义的时候就用二元谓词修饰。
	printVector(v1);
}

