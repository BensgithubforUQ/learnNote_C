#pragma once
#include <iostream>
using namespace std;

//对组的创建和使用
//不需要包括头文件，是非常好用的stl文件
//注意set容器的insert会返回一个对组（迭代器，布尔值），而multiset的insert只会返回一个迭代器

void pair_test0() {
	//第一种构建方式
	pair<string, int>p("Tom", 18);
	cout << "output first element：" << p.first << endl;
	cout << "output second element：" << p.second << endl;
	//第二种方式创建
	pair<string, int>p2 = make_pair("Jerry", 30);
	cout << "output first element：" << p2.first << endl;
	cout << "output second element：" << p2.second << endl;
}
