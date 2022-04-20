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

template<typename T>
void printContainer(const multimap<int, T>& m) {
	for (typename multimap<int, T>::const_iterator it = m.begin(); it != m.end(); it++) {
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

void test_map1() {
	//insert的重载
	map<int, int>m;
	m.insert(pair<int, int>(1, 10));
	m.insert(make_pair(3,30));
	m.insert(map<int,int>::value_type(2,21));
	m[4] = 40;//这个不推荐用，本质是创建key值为4，value为40的pair，容易出错。
	cout << m[5] << endl;//这个m[5]实际上是创建一个key值为5,value为0的值。
	printContainer(m);
	//删除erase
	m.erase(m.begin());
	printContainer(m);
	m.erase(2);//按照key值删除
	printContainer(m);
	m.erase(m.begin(), --m.end());//按照区间的模式删除
	printContainer(m);
	//clear
	m.clear();
	if (!m.empty()) {
		printContainer(m);
	}
	else {
		cout << "blank container" << endl;
	}
	
}

void test_map2() {
	//find,按照key查询
	//count，按照key统计
	multimap<int, int>m;
	m.insert(pair<int, int>(1, 10));
	m.insert(pair<int, int>(1, 10));
	m.insert(pair<int, int>(1, 10));
	m.insert(make_pair(3, 30));
	m.insert(multimap<int, int>::value_type(2, 21));
	//m[4] = 40;//这个不推荐用，本质是创建key值为4，value为40的pair，容易出错。

	map<int, int>::iterator target = m.find(1);
	if (target != m.end()) {
		cout << "找到了: " << target->first << " " << target->second << endl;
		cout << "一共有： " << m.count(1) << endl;
	}
	else {
		cout << "没找到" << endl;
	}

}
class myCompare {
public:
	bool operator()(int p1,int p2) const{
		return p1 > p2;
	}
};

template<typename T>
void printContainer( map<int, T, myCompare>& m) {
	for (typename map<int, T, myCompare>::iterator it = m.begin(); it != m.end(); it++) {
		cout << "key：" << (*it).first << " value:" << it->second << " ";
	}
	cout << endl;
}

void test_map3() {
	map<int, int, myCompare>m;
	m.insert(pair<int, int>(1, 10));
	m.insert(make_pair(3, 30));
	m.insert(map<int, int>::value_type(2, 21));
	m[4] = 40;//这个不推荐用，本质是创建key值为4，value为40的pair，容易出错。
	cout << m[5] << endl;//这个m[5]实际上是创建一个key值为5,value为0的值。
	printContainer(m);
}