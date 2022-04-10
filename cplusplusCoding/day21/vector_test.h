#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "person.h"
using namespace std;

void myPrint(int a) {
	cout << a << endl;
}
/*测试vector容器*/
void test_vector() {
	vector<int> arr_vec;//声明
	arr_vec.push_back(10);//插入数值，vector是尾插法
	arr_vec.push_back(30);
	arr_vec.push_back(20);

	//通过迭代器访问容器中的数据
	vector<int>::iterator itBegin = arr_vec.begin();//起始迭代器，指向第一元素arr_vec[0]，类似指针
	vector<int>::iterator itEnd = arr_vec.end();//结束迭代器，指向最后一个元素后面的一个位置arr_vec[size]
	//第一种遍历方法while循环
	while (itBegin != itEnd) {
		cout << *itBegin << endl;//这里要用解引用来调取数据，因为此处的迭代器，可以当做一个指针
		itBegin++; //指针++，实现在内存中位置移动。
	}
	//第二种遍历方法for循环
	for (vector<int>::iterator it = arr_vec.begin(); it != itEnd; it++) {
		cout << *it << endl;//这里要用解引用来调取数据，因为此处的迭代器，可以当做一个指针
	}
	//第三种方法，for循环auto i:arr_vec
	for (auto i : arr_vec) {
		cout << i << endl;
	}
	//第四种方法，用STL中algorithm中的提供的算法
	for_each(arr_vec.begin(), arr_vec.end(), myPrint);
	//注意，这里运用了回调的技术
	//第一个参数和第二个参数规定了遍历区间，第三个参数一个函数名
	//底层源码是根据区间进行一个for循环遍历，然后返回数值到第三个参数的函数中去
}


//vector 容器中存放自定义的数据类型
void test_vector1() {
	vector<person>p_v;
	person p1("张三", 10, "大墩子镇");
	person p2("李四", 11, "中墩子镇");
	person p3("王五", 12, "小墩子镇");

	//向容器中添加数组
	p_v.push_back(p1);
	p_v.push_back(p2);
	p_v.push_back(p3);

	//遍历容器中的数据
	for (vector<person>::iterator it = p_v.begin(); it != p_v.end(); it++) {
		(* it).showInfo();
	}
}
//vector 容器中存放自定义的数据类型，这次放类对象的指针，把类对象的地址放进去
void test_vector2() {
	vector<person*>p_v;//<person*>类指针
	person p1("张三", 10, "大墩子镇");
	person p2("李四", 11, "中墩子镇");
	person p3("王五", 12, "小墩子镇");

	//向容器中添加数组
	p_v.push_back(&p1);//T *p = &p1 把地址存到容器中
	p_v.push_back(&p2);
	p_v.push_back(&p3);

	//遍历容器中的数据
	for (vector<person*>::iterator it = p_v.begin(); it != p_v.end(); it++) {
		//(*(*it)).showInfo();//(*it)，it是指针，存的是person类对象的地址，因此*it取出来的是person类对象的地址
		//*(*it)，*it是person类对象的地址，再加个*，取出来类对象本身。
		(* it)->showInfo();//这种写法也可以。想想this—>,this也是个指针。
	}
}

//vector容器嵌套容器
void v_V_push_back(int i, vector<vector<int>>&v_V, vector<int> &v1) {//参数为引用
	int max = i + 4;
	for (; i < max; i++) {
		v1.push_back(i);
	}
	v_V.push_back(v1);
}
void test_vector3() {//vector容器，嵌套vector容器，实现一个类似二维数组的容器
	vector<vector<int>>v_V;
	vector<int> v1,v2,v3,v4;
	v_V_push_back(1, v_V, v1);
	v_V_push_back(2, v_V, v2);
	v_V_push_back(3, v_V, v3);
	v_V_push_back(4, v_V, v4);
	for (vector<vector<int>>::iterator it_v = v_V.begin(); it_v != v_V.end(); it_v++) {
		for (vector<int>::iterator it_int = (*it_v).begin(); it_int != (*it_v).end(); it_int++) {
			cout << *it_int <<" ";//*it_int是用迭代器取出来小vector中的值
		}
		cout << endl;
	}
}