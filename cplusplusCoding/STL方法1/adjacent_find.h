#pragma once
#include "vector_base.h"
#include <string>
using namespace std;

//adjacent_find
//查找相邻的重复元素，返回相邻元素的第一个位置的迭代器
//beg开始迭代器
//end结束迭代器

void adjacent_find_test() {
	//adjacent test
	vector<int>v1;
	constructVectorWithSize(v1, 50);
	vector<int>::iterator adjacent_it = adjacent_find(v1.begin(),v1.end());
	if (adjacent_it != v1.end()) {
		printVector(v1);
		cout <<"adjacent elements whose value is same: " << *adjacent_it << " " << *(adjacent_it + 1) << endl;
	}
	else {
		cout << "there are no adjacent elements which have same value" << endl;
	}
}