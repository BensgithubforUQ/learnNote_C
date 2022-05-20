#pragma once
#include "vector_base.h"
#include <string>
#include "find.h"
using namespace std;

//统计内置数据类型
void count_test0() {
	vector<int>v1;
	constructVectorWithSize(v1, 50);
	printVector(v1);
	cout<< "the amount of element with value 5 is :"<< count(v1.begin(), v1.end(), 5)<<endl;
}

//统计自定义的数据类型
void count_test1() {//用find.h中的person类,需要在person类中重载一个==操作符。
	vector<Person>v1;
	v1.push_back(Person("张一", 25));
	v1.push_back(Person("张二", 15));
	v1.push_back(Person("张三", 35));
	v1.push_back(Person("张四", 45));
	v1.push_back(Person("张五", 55));
	v1.push_back(Person("张六", 65));
	///创建一批person对象存入v1
	cout << "the amount of element with value ('张一', 25) is :" << count(v1.begin(), v1.end(), Person("张一",25)) << endl;
}

class greaterFiveCount_if {
public:
	bool operator()(int n) {
		return n > 5;
	}
};

void count_if_test0() {
	//count_if(iterator beg,iterator end,_predicate)三个参数，要加谓词
	vector<int>v1;
	constructVectorWithSize(v1, 50);
	printVector(v1);
	cout << "the amount of element with value 5 is :" << count_if(v1.begin(), v1.end(),greaterFiveCount_if()) << endl;
}

class greaterAgeCount_if {
public:
	bool operator()(const Person &p) {
		return p.p_age > 20;
	}
};

void count_if_test1() {
	vector<Person>v1;
	v1.push_back(Person("张一", 25));
	v1.push_back(Person("张二", 15));
	v1.push_back(Person("张三", 35));
	v1.push_back(Person("张四", 45));
	v1.push_back(Person("张五", 55));
	v1.push_back(Person("张六", 65));
	///创建一批person对象存入v1
	cout << "the amount of element with age > 20 :" << count_if(v1.begin(), v1.end(), greaterAgeCount_if()) << endl;
}