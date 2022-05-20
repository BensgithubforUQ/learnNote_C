#include <iostream>
#include <string>
#include "goldenFingerArray.hpp"
using namespace std;

/*需求
1.可以储存内置数据类型的对象和自定义数据类型的对象
2.将数组中的数据存放到堆区
3.构造函数中可以传入数组的容量
4.提供对应的拷贝构造函数以及operator=的重载防止浅拷贝
5.提供尾插法和尾删法来进行增加或者删除数组中的数据
6.可以通过下标访问
7.可以获取数组中当前元素的个数和数量*/
class cat {//自定义数据类型，用于测试
public:
	cat() {

	}
	cat(string n, int a);
	//cat(string n, int a) {
	//	this->name = n;
	//	this->age = a;
	//}
	string name;
	int age;
};

cat::cat(string n, int a) :name(n), age(a) {
	cout << "初始化列表初始化cat类对象" << endl;
}

void test_goldenFingerArr_0() {
	goldenFingerArray<int>arr1(5);//测试有参构造
	goldenFingerArray<int>arr2(arr1);//测试拷贝构造
	cout << endl;	goldenFingerArray<int>arr3(100);
	arr3 = arr2;//测试重载的操作符"="
}

void test_goldenFingerArr_1() {
	goldenFingerArray<int>arr1(5);//测试有参构造
	for (int i = 0; i < 6; i++) {
		arr1.Push_Back(i);//利用尾插法插入数据，并且测试超出容量的情况
	}
	cout << "arr1打印为" << endl;
	arr1.showArrInfo();

	arr1.Pop_Back();
	arr1.Push_Back(6);

	arr1.showArrInfo();
	cout << "用下标访问：" << arr1[4] << endl;
}

void test_goldenFingerArr_2() {
	//测试自定义的数据类型
	cat kitty("kitty", 10);
	cat tom("tom", 20);
	goldenFingerArray<cat>arr1(5);
	arr1.Push_Back(kitty);
	arr1.Push_Back(tom);
	cout << "容量：" << arr1.getCapacity() << " 长度： " << arr1.getSize() << endl
		<<arr1[1].name<<endl;
	//arr1.showArrInfo();
}
int main() {
	//test_goldenFingerArr_0();
	//test_goldenFingerArr_1();
	test_goldenFingerArr_2();
	system("pause");
	return 0;
}