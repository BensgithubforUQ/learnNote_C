#pragma once
#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

//deque容器被称为双端数组
//如果对vector容器的头部进行插入的话，vector容器需要挪动内存储存的位置，这非常不方便
//但是vector的优势在于访问速度快，因为vector是存在一段连续的线性空间里的
//而deque容器并不是一段连续的线性空间

/*deque和vector的结构很类似，但它是多段连续空间，
如果vector空间不够的时候，要重新分配空间，并把所有的数据复制到新的空间中去，
deque不会这么做，它会去另外开辟一块连续空间去存放数据，
所以存储效率方面deque高于vector,
但deque又不同于链表，它可以说是顺序存储结构和链式存储结构的一个折中方案*/

/*deque中有一个中控器，维护每段缓冲区之中的内容，缓冲区中存放真实数据
中控器存维护的是缓冲区的地址，使使用deque的时候像是在访问一片连续的内存空间
因此，访问元素，deque先要访问中控器中维护的地址，然后通过地址访问对应的缓冲区，然后找到对应的数据*/

/*deque的迭代器也也是支持随机访问的，是最高级的*/
template<typename T>
void printDeque(const deque<T>&deq) {//再次试试函数模板
	for (typename deque<T>::const_iterator it = deq.begin(); it != deq.end(); it++) {//只读迭代器
		cout << *it << " ";
		//加了const之后，就不会再这个函数里面出现修改的情况了，比较安全。
		//注意是const_iterator，不是const iterator
	}
	cout << endl;
}
void test_deque0() {
	//构造函数
	//和vector一样，deque也是默认，拷贝那几种
	deque<int> deq;
	for (int i = 0; i < 10; i++) {
		deq.push_back(i);
	}
	printDeque(deq);
	//用另外一deque的区间初始化
	deque<int>d2(deq.begin(), deq.end());
	printDeque(d2);
	//复数个n初始化
	deque<int>d3(10, 9);
	printDeque(d3);
	//用另一个deque容器之间初始化，拷贝初始化
	deque<int>d4(d3);
	printDeque(d4);
}

void test_deque1() {
	//赋值操作
	//也和vector基本上一样
	deque<int>d1, d2, d3, d4;
	d1.assign(10, 9);//n个m值的赋值方式
	printDeque(d1);
	d2 = d1;//拷贝的方式
	printDeque(d2);
	for (int i = 0; i < 10; i++) {
		d3.push_back(i);
	}
	d4.assign(d3.begin() + 1, d3.end());
	printDeque(d3);
	printDeque(d4);//assign区间的赋值方式
}

void test_deque2() {
	//deque容器的大小操作,重新指定大小操作,和vector的区别在于，deque没有容量的概念。
	deque<int>d1;
	d1.assign(10, 9);
	printDeque(d1);
	cout << "d1的大小为：" << d1.size() << endl;
	//resize
	d1.resize(20);
	printDeque(d1);//多余的空间用0补足
	cout << "d1的大小为：" << d1.size() << endl;
	//resize更小的长度
	d1.resize(5);
	printDeque(d1);
	cout << "d1的大小为：" << d1.size() << endl;
	cout << "resize的妙用" << endl;
	if (!d1.empty()) {
		cout << "d1.empty()的值为：" << d1.empty() << endl;//为0，不为空
		cout << "d1不为空" << endl;
		cout << "d1的大小为：" << d1.size() << endl;
		d1.resize(0);
	}
	if (d1.empty()) {
		cout << "d1为空" << endl;
		cout << "d1的大小为：" << d1.size() << endl;
	}
}

void test_deque3(){
	//push_back,pop_back,pop_front,push_front
	//insert,erase,clear
	//两端的插入和删除
	deque<int>d1;
	d1.push_back(20);
	d1.push_back(21);
	d1.push_front(19);
	d1.push_front(18);
	printDeque(d1);
	d1.pop_front();
	d1.pop_back();
	printDeque(d1);
	//insert
	d1.insert(d1.begin() + 1, 111);//传入迭代器表示位置，和一个需要插入的值
	printDeque(d1);
	d1.insert(d1.begin() + 1, 3, 20);//传入迭代器表示位置，和n个需要插入的值
	printDeque(d1);
	deque<int>d2(9, 9);
	printDeque(d2);
	d1.insert(d1.begin(), d2.end() - 3, d2.end());//根据区间插入，另外一个迭代器的区间
	printDeque(d1);
	//erase删除
	deque<int>::iterator it = d1.begin() + 3;
	d1.erase(it);
	printDeque(d1);//删除指定位置的值。
	d1.erase(d1.begin()+1, it);
	printDeque(d1);
	//clear
	d1.clear();
	printDeque(d1);//直接清空了
}

void test_deque4() {
	//[] at,front,back
	deque<int>d1;
	d1.push_back(20);
	d1.push_back(21);
	d1.push_front(19);
	d1.push_front(18);
	//[]
	cout << "用[]访问" << endl;
	for (int i = 0; i != d1.size(); i++) {
		cout << d1[i] << " ";
	}
	cout <<endl << "用迭代器访问" << endl;
	//*迭代器
	for (deque<int>::const_iterator it = d1.begin(); it != d1.end(); it++) {
		cout << *it << " ";
	}
	
	cout << endl << "用at访问" << endl;
	//at
	for (int i = 0; i != d1.size(); i++) {
		cout << d1.at(i) << " ";
	}
	//front & end
	cout << endl << "front & end" << endl;
	cout << d1.front() << " " << d1.back() << endl;
}

void test_deque5() {
	//排序，用algorithm里面的sort
	deque<int>d1;
	for (int i = 0; i < 10; i++) {
		d1.push_back(i);
		d1.push_front(i);
	}
	printDeque(d1);//打印一波
	sort(d1.begin(),d1.end());
	cout << "sort后的顺序,默认升序算法" << endl;
	printDeque(d1);
	//对于支持随机访问的迭代器的容器，都可以用sort，比如vector。
}