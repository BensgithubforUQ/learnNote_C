#pragma once
#include <iostream>
#include <set>
#include <list>
#include <time.h>
#include "Person.h"
using namespace std;

template<typename T>
class  MyCompare;



/*set属于关联式容器，底层结构是二叉树，所有元素在插入的时候会自动排序*/
/*set和multiset的区别
set不允许重复元素，multiset允许重复元素*/
template <typename T>
void printContainer(set<T> &s1) {//函数模板，打印set容器的内容
	if (!s1.empty()) {
		cout << "size: " << s1.size() << " set :";
		for (typename set<T>::const_iterator it = s1.begin(); it != s1.end(); it++) {
			cout << *it << " ";
		}
	}
	else {
		cout << "it is NULL";
	}
	cout << endl;
}



template <typename T>
void printContainer(multiset<T>& s1) {//函数模板，打印multiset容器的内容
	if (!s1.empty()) {
		cout << "size: " << s1.size() << " set :";
		for (typename multiset<T>::const_iterator it = s1.begin(); it != s1.end(); it++) {
			cout << *it << " ";
		}
	}
	else {
		cout << "it is NULL";
	}
	cout << endl;
}

template <typename T>
void printContainer(list<T>& l1) {//函数模板，打印链表容器的内容
	if (!l1.empty()) {
		for (typename list<T>::const_iterator it = l1.begin(); it != l1.end(); it++) {
			cout << *it << " ";
		}
	}
	else {
		cout << "it is NULL";
	}
	cout << endl;
}

template <typename T>
void printContainer(set<T,MyCompare<T>>& s1) {//函数模板，打印带排序规则的set容器的内容
	//知识点，类模板的提前声明，类模板的使用，仿函数+类模板+STL容器+函数模板同时使用
	//重载，封装
	if (!s1.empty()) {
		cout << "size: " << s1.size() << " set :";
		for (typename set<T>::const_iterator it = s1.begin(); it != s1.end(); it++) {
			cout << *it << " ";
		}
	}
	else {
		cout << "it is NULL";
	}
	cout << endl;
}


void set_test0() {
	srand((unsigned int)time(NULL)); //整个随机数种子
	//构造
	set<double> s1,s3;
	list<double> l1;
	for (int i = 10; i > 0; i--) {
		double temp = i + (rand() % 99 + 0) + (rand() / double(RAND_MAX));
		s1.insert(temp);//乱序输入
		l1.push_back(temp);
		if (i == 10) {
			//搞事，传入相同的数据
			s1.insert(temp);
			l1.push_back(temp);
		}
	}
	printContainer(s1);  //但是打印的时候，出来的是升序的，这体现了set的排序特性。
	printContainer(l1); //打印一下链表容器，比较下结果
	cout << "链表的长度：" << l1.size() << " set容器的长度 " << s1.size() << endl;
	//构造2
	set<double > s2(s1);
	// = 赋值
	s3 = s2;
	//printContainer(s3);
}

void set_test1() {
	srand((unsigned int)time(NULL)); //整个随机数种子
	set<double> s1, s2;
	for (int i = 10; i > 0; i--) {
		s1.insert((rand()%99 + 1) + (rand()/double(RAND_MAX)));//乱序输入
		s2.insert((rand() % 99 + 1) + (rand() / double(RAND_MAX)));//乱序输入，随机输入
		//搞事
		if (i == 10) {
			s2.insert((rand() % 99 + 1) + (rand() / double(RAND_MAX)));
		}
	}
	printContainer(s1);
	printContainer(s2);
	s1.swap(s2);//针对不同长度的set容器也可以用
	printContainer(s1);
	printContainer(s2);
}

void set_test2() {
	set<int> s1;
	s1.insert(11);
	s1.insert(12);
	s1.insert(10);
	s1.insert(8);
	printContainer(s1);
	s1.erase(s1.begin()); //用迭代器删
	printContainer(s1);
	s1.erase(10);
	printContainer(s1); //按值删
	set<int>s2(s1);
	s1.clear();//清空
	printContainer(s1);
	s2.erase(s2.begin(), s2.end());
	printContainer(s2);
}

void set_test3() {
	//find和count
	multiset<int> s1; //multiset就是可以重复元素的set
	s1.insert(11);
	s1.insert(11);
	s1.insert(11);
	s1.insert(11);
	s1.insert(12);
	s1.insert(10);
	s1.insert(8);
	multiset<int>::iterator it_11 = s1.begin();
	//multiset<int>::iterator it_11 = s1.find(11); //如果存在11，返回的是11对应的迭代器，如果不存在返回end（）
	/*if (it_11 != s1.end()) {
		cout << "11存在 " <<s1.count(11) <<" 个" << endl;

	}*/
	int i = 0;
	do
	{
		++i;
		it_11 = s1.find(11);
		printContainer(s1);
		cout << "11存在 " << s1.count(11) << " 个" << endl;
		//cout << "删第一个11" << endl;
		//s1.erase(it_11);//这里不能删，因为这里有个迭代器在用，set和list不同，迭代器必须依托于一个不变的容器
		//*it_11,这是个const啊!!!!!
		if (i > s1.size()) {
			break;//这个循环注定死循环hh
			//因为没法改set容器里面的数据
		}

	} while (it_11 != s1.end());
}
//封装个判断是否插入成功的函数
//template <typename T>
//void insertFeedback(pair<typename set<T>::iterator, bool> ret) {
void insertFeedback(bool target){
	if(target) {
		cout << "插入成功" << endl;
	}
	else{
		cout << "插入失败" << endl;
	}
}
void set_test4() {
	//set和multiset的区别
	set<int> s1;
	multiset<int> s2;
	cout << "insert multiple same element into a set" << endl;
	for (int i = 0; i < 10; i++) {
		pair<set<int>::iterator, bool> ret = s1.insert(10);
		// insertFeedback是我自己封装的用来判断是否插入成功的函数
		insertFeedback(ret.second);
		//pair为对组，是一种数据类型，而s1.insert（）会返回两个值，一共是插入的位置，一共是是否插入成功
	}
	cout << "insert multiple same element into a multiset" << endl;
	for (int i = 0; i < 10; i++) {
		multiset<int>::iterator pos = s2.insert(10);
		//multiset的insert没有返回对组数据类型，直接返回的是一个迭代器。
		// insertFeedback是我自己封装的用来判断是否插入成功的函数
		insertFeedback(pos != s2.end());
		//pair为对组，是一种数据类型，而s1.insert（）会返回两个值，一共是插入的位置，一共是是否插入成功
	}
	
}

template<typename T>
class  MyCompare {//仿函数
public:
	bool operator()(T first,T second) const;//重载（），注意这个地方如果不加const会报错
	
	/*Error C3848 : expression having type ‘const myCompare’ 
		would lose some const - volatile qualifiers in order to call 
		‘bool myCompare::operator ()(int, int)’*/
		//volatile相关
		// 
//报错内容大概意思为:传入的参数表达式应具有“const myCompare”类型，
//而你调用的“bool myCompare::operator ()(T, T)”不具备const属性，
//会丢失const限定，所以无法通过编译。
//
//故只要将operator()具有const属性便可，如下

};

template<typename T>
bool MyCompare<typename T>::operator() (T first, T second) const {
	
	return first > second;
}



//set容器的排序逻辑
void set_test5() {
	//仿函数再次试用。
	//set容器存放内置的数据类型的排序逻辑
	set<int> s1;
	for (int i = 10; i > 0; i--) {
		s1.insert(i);//插入数据,这里会自动做成升序
	}
	printContainer(s1);
	//指定排序规则为降序
	//因为set容器是在默认排序的，因此要在创建set容器的时候，就设定好如何排序
	set<int, MyCompare<int>> s2;
	
	for (int i = 10; i > 0; i--) {
		s2.insert(i);
	}
	printContainer(s2);//经过研究，重载+封装了添加排序规则版本的set容器的打印方式。
	//for (set<int>::iterator it = s2.begin(); it != s2.end(); it++) {
	//	cout << *it << " ";
	//}
}



//set容器的排序逻辑-自定义数据类型的排序
//用person类作为实验对象----------------------------------------------------------------------
class myCompare_Person {//仿函数
public:
	bool operator()(const Person& p1, const Person& p2) const;//重载（）,自定义数据类型的排序规则设定
};
bool myCompare_Person::operator()(const Person& p1, const Person& p2) const {
		if (p1.getAge() == p2.getAge()) return p1.getheight() < p2.getheight();
		return p1.getAge() > p2.getAge();//这个地方试了好久怎么让person类中还是private的数据类型
		//但是失败了，最终还是把person改成了public的数据类型，不然这个地方始终报错，暂时不知道怎么解决
}
void printContainer(set<Person, myCompare_Person>& s1) {
	//说下这里的坑，首先这里的set的排序规则要加上，不然找不到排序规则
	//其次，这里和其他函数模板并不是特例关系，直接单独出来写
	//再次，必须把仿函数的定义写在这个前面。
	if (!s1.empty()) {
		cout << "size: " << s1.size() << " set :";
		for (typename set<Person>::iterator it = s1.begin(); it != s1.end(); it++) {
			it->showInfo();
		}
	}
	else {
		cout << "it is NULL";
	}
	cout << endl;
}


//set容器的排序逻辑-自定义数据类型的排序
//用person类作为实验对象
void set_test6() {
	int size = 10;
	set<Person, myCompare_Person> s_p;
	for (int i = 0; i < size; i++) {
		char name_temp = (i + 65);
		string name{ name_temp };
		int age = rand() % 25 + 20;
		float height = (rand() % 30 + 160) + (rand() / double(RAND_MAX));
		Person p_temp(name, age, height);
		s_p.insert(p_temp);//这里如果直接输入的话，就会报错，因为这个会排序
		//毕竟，编译器不知道怎么比较自定义数据类型的大小，就更不会排序
		/*error C2676 : 二进制“ < ” : “const _Ty”不定义该运算符或到预定义运算符可接收的类型的转换*/
		//因此自定义的数据类型多半会指定排序规则
		//因此这里还是要用到仿函数，仿函数本质是个类。
	}
	printContainer(s_p);
}