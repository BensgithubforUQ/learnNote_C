#pragma once
#include "vector_base.h"
#include <string>
#include "find.h"
using namespace std;

void copy_test0() {
	//拷贝指定范围内的元素到另外一个容器中
	//copy（begin，end，destination）
	vector<int>v1, v2;
	constructVectorWithSize(v1, 10);
	v2.resize(v1.size());
	copy(v1.begin(), v1.end(), v2.begin());
	for_each(v2.begin(), v2.end(), PrintInt_functor());
}

void replace_test0() {
	//将指定区间内的元素改成新元素
	vector<int>v1;
	constructVectorWithSize(v1, 10);
	sort(v1.begin(), v1.end());//默认升序
	for_each(v1.begin(), v1.end(), printInt_function);
	cout << endl;
	//replace替换
	if (count(v1.begin(), v1.end(), 9) != 0) {
		replace(v1.begin(), v1.end(), 9, 5);
		for_each(v1.begin(), v1.end(), printInt_function);
	}
	else {
		cout << "v1中，没有9" << endl;
		for_each(v1.begin(), v1.end(), printInt_function);
	}
}

void replace_if_test0() {
	//将指定区间内的元素按照自定义规则，改成新元素
	//将指定区间内的元素改成新元素
	vector<int>v1;
	constructVectorWithSize(v1, 10);
	sort(v1.begin(), v1.end());//默认升序
	for_each(v1.begin(), v1.end(), printInt_function);
	cout << endl;
	//replace替换
	if (count_if(v1.begin(), v1.end(), greaterFive()) != 0) {
		replace_if(v1.begin(), v1.end(), greaterFive(), 5);
		cout << "已经将大于5的数都替换了" << endl;
		for_each(v1.begin(), v1.end(), printInt_function);
	}
	else {
		cout << "v1中，没有大于5的数" << endl;
		for_each(v1.begin(), v1.end(), printInt_function);
	}
}

void swap_test0() {
	//同种类型的容器，元素互换
	vector<int>v1;
	constructVectorWithSize(v1, 10);
	vector<int>v2;
	constructVectorWithSize(v2, 20);
	printVector(v1);
	printVector(v2);
	cout << "v1 size " << v1.size() << " v2 size " << v2.size() << endl;
	//swap
	swap(v1, v2);
	printVector(v1);
	printVector(v2);
	cout << "v1 size " << v1.size() << " v2 size " << v2.size() << endl;
	//连size都换了。
}

