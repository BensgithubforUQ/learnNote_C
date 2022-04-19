#pragma once
#include <map>
#include <iostream>
using namespace std;

/*map是关联型容器，所有的元素都是pair，第一个值为key键值，第二个元素为value实值
所有元素都会根据key键值自动排序
底层结构是二叉树

优点：可以根据key值快速找到value值，这是set不具备的，set只能根据值找迭代器位置
*/
template<typename T>
void printContainer(const map<int,T> &m) {
	for (typename map<int, T>::const_iterator it = m.begin(); it != m.end(); it++) {
		cout << "key：" << (*it).first << " value:" << it->second << " ";
	}
	cout << endl;
}
void test_map0() {
	map<int, int>m0;
	m0.insert(pair<int, int>(1, 10));//pair<int, int>(1, 10)是一个匿名的pair类型
	m0.insert(pair<int, int>(3, 30));
	m0.insert(pair<int, int>(2, 20));
	m0.insert(pair<int, int>(4, 40));
	m0.insert(pair<int, int>(6, 60));
	m0.insert(pair<int, int>(5, 50));
	m0.insert(pair<int, int>(7, 70));//按照key值排序，不是按照value
	printContainer(m0);
	//拷贝构造
	map<int, int>m1(m0);
	m1.insert(pair<int, int>(8, 80));
	printContainer(m1);
	//赋值
	map<int, int>m3;
	m3 = m1;
	printContainer(m3);
	//map容器的大小和交换
	//size返回容器内元素个数，empty
	//swap
	if (!m1.empty()) {
		cout << "m1不是空的容器，其大小为：" << m1.size() << endl;
	}
	m1.swap(m0);//交换
	printContainer(m0);
}