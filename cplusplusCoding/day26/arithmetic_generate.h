#pragma once
#include "vector_base.h"
#include <string>
#include <numeric>
using namespace std;

//arithmetic generation
/*属于小型算法，头文件为numeric*/

void  accumulate_test() {
	vector<int>v1;
	int val = 0,sum = 0;
	constructVectorWithSize(v1, 100);
	
	for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
		sum += *it;
	}
	if (accumulate(v1.begin(), v1.end(), val) == sum) {//val为起始的累加值。
		cout << "累加值为：" << sum << endl;
	}
	else {
		cerr << "算法出现问题" << endl;
	}
}

void  fill_test() {
	//填充算法，把指定容器内指定的区间填充成目标元素
	vector<int>v1;
	constructVectorWithSize(v1, 10);
	printVector(v1);
	v1.resize(20,5);//resize可以扩的时候指定值，不指定则为0
	printVector(v1);
	fill((v1.begin() + 10), v1.end(), 10);
	printVector(v1);
}