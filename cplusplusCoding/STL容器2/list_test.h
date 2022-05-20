#pragma once
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

//链表，链表和数组不同，数组是连续的线性空间，而链表则不是，链表依靠每个节点来记录相邻的节点的位置
//节点由数据域和指针域构成，数据域显示储存的数据，结点的指针域维护着相邻的结点的地址，最后一个指向NULL
/*链表的优点：
可以对任意的位置，通过操作指针域的方式，进行快速的添加，插入，删除
不会造成大量的空间浪费，因为结点是一个个创造的，不会想数组那样一次性分配大量的内存空间*/
/*链表的缺点：
首先对于容器的遍历速度，没有数组快。因为数组的内存空间是连续的。
占用的空间，会比数组要大。因为链表还多个指针域，指针要占四个空间（x32）*/
//数组和链表的优缺点是互补的，需要根据情况择优而用

/*STL中封装的list操作，是一个双向循环的。
list容器有两个指针，一个指向前一个结点，一个指向下一个结点。并且链表头和链表尾相连
但是stl的链表仍有头尾之分，有begin，end，push_front,push_back,pop_front,等
因为不是连续的内存空间，因此迭代器不也是随机访问的，是双向迭代器，只支持前移后移
*/

//重要性质，vector中，不可以一边删除增加容器，一边用一个迭代器去访问数据，但是list中可以。
//list和vector是最常用的容器，所以是重中之重。
//回调函数myCompare，用于实现降序排列
bool myCompare(int v1, int v2) {
	//降序 就让第一个数 > 第二个数
	return v1 > v2;
	//这里v1>v2就会返回一个布尔值，如果大于就会返回真
}

template<typename T>
void printList(const list<T> &l) {
	if (!l.empty()) {
		for (typename list<T>::const_iterator it = l.begin(); it != l.end(); it++) {
			cout << *it << " ";
		}
	}
	else {
		cout << "空链表捏" << endl;
	}
	cout << endl;
}

void list_test0() {//一系列基本list容器的操作
	//构造函数
	list<int>l1,l4,l5;
	list<int>l2(10, 9);
	list<int>l3(l2);

	//赋值一下
	for (int i = 0; i < 10; i++) {
		l1.push_back(i+10);
	}
	//赋值assign
	l4.assign(l1.begin(), l1.end());//这里因为不是连续内存地址，因此不能+-地址的操作
	printList(l1);
	printList(l2);
	printList(l3);
	printList(l4);
	cout << "l5的size: " << l5.size() << endl<<"对l1 & l5进行swap操作"<<endl;
	l5.swap(l1);
	if (!l5.empty()) {//l5？=0
		cout << "l5.empty() :" << l5.empty() << endl;
		printList(l5);
		//resize
		cout << "l5.resize(5);" << endl;
		l5.resize(5);
		printList(l5);
		//resize
		cout << "l5.resize(10);" << endl;
		l5.resize(10,1024);//第二个参数可以重设填充数据
		printList(l5);
	}
	//list容器的插入和删除
	cout << "list容器的插入和删除" << endl;
	for (int i = 0; i < 10; i++) {
		l1.push_back(i + 10);
		l1.push_front(i + 100);
	}
	//尾插和头插的结果
	cout << "尾插和头插的结果： ";
	printList(l1);
	//头删1个元素，尾删2个元素
	l1.pop_back();
	l1.pop_back();
	l1.pop_front();
	cout << "头删1个元素，尾删2个元素： ";
	printList(l1);
	//insert插入
	list<int>::iterator it = l1.begin();
	++it;//不能+value，但是可以++，体现了双向迭代器的特点，只能一个个加，或者一个个减，不支持随机访问的体现。
	l1.insert(it, 1024);
	cout << "//insert插入,在头部后面一个结点插入，1024： ";
	printList(l1);
	//删除 erase
	//l1.erase(++it);
	//l1.erase(it);
	//这里出现了一个很有趣的情况，这里的it维护的仍然是上一次insert之前的结点。
	//重要性质，vector中，不可以一边删除增加容器，一边用一个迭代器去访问数据，但是list中可以。
	//因此如果这里++it，删除的是实际链表中的第四个数据
	//如果这里删除it，删除的实际是没有insert之前，it记录的数据
	//最好重新定义一个迭代器来查找，避免陷入混乱,或者重新赋值为一个可以确定位置的锚点。
	list<int>::iterator it_2 = l1.begin();
	++(++it_2);
	l1.erase(it_2);
	cout << "//删除 erase,第三结点： ";
	printList(l1);
	//remove
	cout << "先插入一些一样的数据" << endl;
	for (int i = 0; i < 10; i++) {
		l1.push_back(100);
		l1.push_front(100);
	}
	printList(l1);
	cout << "//删除remove所有的100： ";
	l1.remove(100);
	printList(l1);
	//清空clear
	l1.clear();
	cout << "//clear ";
	printList(l1);
	//访问front和back
	cout << "l5的元素为 ";
	printList(l5);
	cout << "访问front： " << l5.front() << " 访问back ：" << l5.back() << endl;
	//list的反转和排序
	cout << "//list反转： ";
	l5.reverse();
	printList(l5);
	cout << "//list排序： ";
	//sort(l5);
	//所有，双向迭代器的容器（不支持随机访问的迭代器的容器），都不支持算法标准模板库中封装的sort方法
	//因此，会在容器中封装sort操作。
	l5.sort();//默认升序
	printList(l5);
	cout << "//list排序（降序）： ";
	//特殊操作，往上翻函数
	l5.sort(myCompare);//sort的myCompare函数回调，先死记。
	printList(l5);
}