#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "person.h"
using namespace std;

//vector 也被称为单端数组
//数组是静态空间的，不可以动态扩展
//动态扩展并不是在原有的空间后面添加新空间，而是根据所需空间大小，把原来的数据拷贝过去。
//vector的首端是封闭的，不可以插数据
//vector可以尾插和尾删，还可以insert和erase（删除）
//vector的迭代器是可以随机访问的，是最强大的一种迭代器
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

//封装一个vector的打印
template<typename T>//小小的复习一下函数模板
void printVector(vector<T> &v) {
	for(typename vector<T>::iterator it = v.begin();it!=v.end();it++){//typename必须被加上，以防二义性
		//因为还有其他语法会用到::,<>这个东西，所以在T是个类型的时候，前面最好加typename
		cout << *it <<" ";
	}
	cout << endl;
}

void test_vector4() {
	vector<int> v1;//无参构造，默认构造
	for (int i = 0;i<10;i++){
		v1.push_back(i);
	}
	printVector(v1);
	//利用区间的方式构造
	vector<int>v2(v1.begin(), v1.end()-1);//根据另外一个vector容器的区间来构造,这里还可以试试位置计算。
	printVector(v2);
	//n个elements的构造办法
	vector<char>v3(10, 'a');
	printVector(v3);
	//拷贝构造
	vector<char>v4(v3);
	printVector(v4);
}

void test_vector5() {
	//赋值主要由重载的=和封装的assign函数来操作
	//=
	vector<int> v1;
	vector<int> v2(10, 9);
	v1 = v2;
	printVector(v1);
	//assign
	v2.push_back(8);
	v1.assign(v2.begin()+10, v2.end());//注意这里面一定传参的是地址，不是值。
	printVector(v1);

	//加n个数
	v1.assign(10, 7);
	printVector(v1);
}

void test_vector6() {
	//容量和大小
	//empty和capacity，size
	vector<char>v_char;
	for (int i = 65; i < 91; i++) {
		v_char.push_back((char)i);
	}
	printVector(v_char);

	cout << "是否为空？0为不空" << v_char.empty() << endl;
	cout << "容量大小？" << v_char.capacity() << endl;
	cout << "容器长度？" << v_char.size() << endl;
	cout << "这里容器的长度和容量大小的不一样，体现了vector的动态扩展的特性" << endl;
	//重新设置长度，长度太长的话，默认用0补足
	v_char.resize(11);
	printVector(v_char);
	cout << "是否为空？0为不空 " << v_char.empty() << endl;
	cout << "容量大小？" << v_char.capacity() << endl;
	cout << "容器长度？" << v_char.size() << endl;
}

void test_vector7() {
	//插入和删除，这里需要用迭代器，不可以用值，也就是说要用地址，同理上面的那个end和begin
	vector<int>v1(10, 9);
	//尾插法
	v1.push_back(11);
	printVector(v1);
	//尾删法
	v1.pop_back();
	printVector(v1);
	//insert
	v1.insert(v1.begin(), 8);
	printVector(v1);
	v1.insert(v1.begin()+5,3 ,10);//还可以插n个一样的数据
	printVector(v1);
	//erase 删除，可以删除区间，也可以删除单个，记得是输入迭代器
	v1.erase(v1.begin() + 5,v1.begin()+8);
	printVector(v1);
	//clear 清空
	v1.clear();
	printVector(v1);
	if (v1.empty()) {
		cout << "blank" << endl;
	}
}

void test_vector8() {
	//at和[]访问，front和back
	vector<char>v_char;
	for (int i = 65; i < 91; i++) {
		v_char.push_back((char)i);
	}
	printVector(v_char);
	//front
	cout << "front: " << v_char.front() << endl;
	//back
	cout << "back: " << v_char.back() << endl;
	//at
	cout << "at.倒数第一个: " << v_char.at(v_char.size() - 1) << endl;
	//[]
	cout << "[]： " << v_char[0] << endl;
}

void test_vector9() {
	vector<int> v1;
	for (int i = 0; i < 10; i++) {
		v1.push_back(i);
	}
	vector<int> v2(5, 10);
	//vector容器的置换
	cout << "交换前：" << endl;
	printVector(v1);
	printVector(v2);
	cout << "交换后：" << endl;
	v1.swap(v2);
	printVector(v1);
	printVector(v2);
	//巧用swap可以收缩内存空间
	vector<int>v3(10000001, 5);
	cout << "v3容量大小？" << v3.capacity() << endl;
	cout << "v3容器长度？" << v3.size() << endl;
	//这里操作一波，把这10000001的长度删了，用resize恶心一下
	v3.resize(3);
	cout << "resize后v3容量大小？" << v3.capacity() << endl;
	cout << "v3容器长度？" << v3.size() << endl;
	//这种情况就可以用swap收缩一下
	//vector<int>(v3),匿名对象，新对象无名，但是用v3来拷贝构造
	//.swap就是把这个匿名对象和v3交换
	//注意，这里这个匿名对象就只有三个值，并且容量也只分了三个
	cout << "匿名对象容量大小？" << vector<int>(v3).capacity() << endl;
	cout << "匿名对象容器长度？" << vector<int>(v3).size() << endl;
	vector<int>(v3).swap(v3);
	//打印一下交换后的v3的容量和容器长度
	cout << "swap+resize后v3容量大小？" << v3.capacity() << endl;
	cout << "v3容器长度？" << v3.size() << endl;
}

void test_vector10() {
	//预留空间reserve
	vector<int> v1;
	v1.reserve(10);
	cout << "v1初始化后reserve（10）容量大小？" << v1.capacity() << endl;
	cout << "v1初始化后reserve（10）容器长度？" << v1.size() << endl;
	//预留空间的意义
	//设想要存一个巨大的数据
	int* p = NULL;
	vector<int> v2;
	//v2.reserve(10000000);
	// 这里就是reserve的功效，如果已知需要开辟巨大的空间的话，可以提前用reserve预留。
	//vector<int>::iterator p = v2.begin();
	int i = 0,num = 0;
	while (i < 10000000) {
		v2.push_back(i);
		if (p != &v2[0]) {
		//if (p != v2.begin()) {//注意这里实践了一种vector改变的时候使用迭代器的操作
			//注意，迭代器和容器一一对应，一旦容器变化，迭代器就不能用了。
			p = &v2[0];
			//p = v2.begin();
			num++;
		}
		i++;
	}
	cout << "动态扩展了：" << num << " 次" << endl;
	//这里发现，如果不用reserve这里动态扩展了四十多次，这是非常严重的问题

}