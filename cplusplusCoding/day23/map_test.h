#pragma once
#include <map>
#include <iostream>
using namespace std;

/*map是关联型容器，所有的元素都是pair，第一个值为key键值，第二个元素为value实值
所有元素都会根据key键值自动排序
底层结构是二叉树

优点：可以根据key值快速找到value值，这是set不具备的，set只能根据值找迭代器位置
*/


void test_map0() {
	map<int, int>m0;
	m0.insert(pair<int, int>(1, 10))//pair<int, int>(1, 10)是一个匿名的pari类型

}