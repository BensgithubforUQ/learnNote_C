#pragma once
#include "vector_base.h"
#include <string>
#include "find.h"
using namespace std;

//sort排序
//sort(begin ,end,predicate)

class sortByPersonAgeDescending {
public:
	bool operator()(Person &p1, Person& p2) {
		return p1.p_age > p2.p_age;
	}
};

void sort_test0() {//直接整自定义数据类型的
	vector<Person>v1;
	v1.push_back(Person("张一", 25));
	v1.push_back(Person("张二", 15));
	v1.push_back(Person("张三", 35));
	v1.push_back(Person("张四", 45));
	v1.push_back(Person("张五", 55));
	v1.push_back(Person("张六", 65));
	printVector(v1);
	sort(v1.begin(), v1.end(), sortByPersonAgeDescending());
	printVector(v1);
}

void randomshuffle_test0() {
	//洗牌算法 random_shuffle(begin ,end);
	vector<Person>v1;
	v1.push_back(Person("张一", 25));
	v1.push_back(Person("张二", 15));
	v1.push_back(Person("张三", 35));
	v1.push_back(Person("张四", 45));
	v1.push_back(Person("张五", 55));
	v1.push_back(Person("张六", 65));
	printVector(v1);
	sort(v1.begin(), v1.end(), sortByPersonAgeDescending());
	printVector(v1);
	random_shuffle(v1.begin(), v1.end()); //打乱排列
	printVector(v1);
}

void merge_test0() {
	//将两个容器的合并，并且存到一个容器中
	/*这两个容器，必须是有序的。合并之后依然是个有序的序列*/
	vector<Person>v1;
	v1.push_back(Person("张一", 25));
	v1.push_back(Person("张二", 15));
	v1.push_back(Person("张三", 35));
	v1.push_back(Person("张四", 45));
	v1.push_back(Person("张五", 55));
	v1.push_back(Person("张六", 65));
	vector<Person>v2;
	v2.push_back(Person("李一", 25));
	v2.push_back(Person("李二", 15));
	v2.push_back(Person("李三", 35));
	v2.push_back(Person("李四", 45));
	v2.push_back(Person("李五", 55));
	v2.push_back(Person("李六", 65));
	sort(v1.begin(), v1.end(), sortByPersonAgeDescending());
	sort(v2.begin(), v2.end(), sortByPersonAgeDescending());
	vector<Person>v3;
	v3.resize(v1.size() + v2.size());//对于自定义的数据类型，这步要加上
	//不然会报错，cannot seek value initialized vector iterator
	//因为v3没有初始化，没有begin。
	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin(), sortByPersonAgeDescending());
	//（begin1，end1，begin2，end2，begin3）
	printVector(v3);
}

void reverse_test() {
	//自定义数据类型的reserve
	vector<Person>v1;
	v1.push_back(Person("张一", 25));
	v1.push_back(Person("张二", 15));
	v1.push_back(Person("张三", 35));
	v1.push_back(Person("张四", 45));
	v1.push_back(Person("张五", 55));
	v1.push_back(Person("张六", 65));
	sort(v1.begin(), v1.end(), sortByPersonAgeDescending());
	printVector(v1);
	reverse(v1.begin(), v1.end());
	printVector(v1);
	cout << endl;

}