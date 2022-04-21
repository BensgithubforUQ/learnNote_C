#pragma once
#include "vector_base.h"
#include <string>
using namespace std;

//查找内置的数据类型
class Person {
public:
	string p_name;
	int p_age;
	Person() {
		this->p_name = " ";
		this->p_age = 0;
	}
	Person(string n, int a) {
		this->p_name = n;
		this->p_age = a;
	}
	bool operator==(const Person &p) { //重载一波==
		if (p.p_name == this->p_name && p.p_age == this->p_age) {
			return true;
		}
		else {
			return false;
		}
	}

};

//find内置数据类型
void find_test() {
	vector<int>v1;
	constructVectorWithSize(v1, 5);
	vector<int>::iterator it = find(v1.begin(),v1.end(),5);
	if (it == v1.end()) {
		cout << "没有找到5" << endl;
	}
	else {
		cout << *it << " position is " <<it-v1.begin() << endl;
	} 
}

//find自定义数据类型
void find_test1() {
	vector<Person>v1;
	v1.push_back(Person("张一", 25));
	v1.push_back(Person("张二", 15));
	v1.push_back(Person("张三", 35));
	v1.push_back(Person("张四", 45));
	v1.push_back(Person("张五", 55));
	v1.push_back(Person("张六", 65));

	vector<Person>::iterator it = find(v1.begin(), v1.end(), Person("张一",25));
	if (it == v1.end()) {
		cout << "没有找到5 " << endl;
	}
	else {
		cout << it->p_name <<it->p_age<<it - v1.begin() << endl;
	}
}

class greaterFive {
public:
	bool operator()(int n) {
		return n > 5;
	}
	bool operator()(Person p) {
		return p.p_age > 25;
	}
};
//find_if 查找内置数据类型
void find_if_test() {
	vector<int>v1;
	constructVectorWithSize(v1, 5);
	vector<int>::iterator it = find_if(v1.begin(), v1.end(), greaterFive());
	if (it == v1.end()) {
		cout << "没有找到大于5的数字" << endl;
	}
	else {
		cout << *it << " position is " << it - v1.begin() << endl;
	}
}

//find_if 查找自定义数据类型
void find_if_test1() {
	vector<Person>v1;
	v1.push_back(Person("张一", 25));
	v1.push_back(Person("张二", 15));
	v1.push_back(Person("张三", 35));
	v1.push_back(Person("张四", 45));
	v1.push_back(Person("张五", 55));
	v1.push_back(Person("张六", 65));

	vector<Person>::iterator it = find_if(v1.begin(), v1.end(), greaterFive());
	if (it == v1.end()) {
		cout << "没有找到大于5的数字" << endl;
	}
	else {
		cout << it->p_name << it->p_age << it - v1.begin() << endl;
	}
}

void printVector(const vector<Person> v) {
	if (!v.empty()) {
		for (auto it = v.begin(); it != v.end(); it++) {
			cout << it->p_name << " " << it->p_age << " ";
		}
		cout << endl;
	}
	else {
		cerr << "blank vector" << endl;
	}
}

