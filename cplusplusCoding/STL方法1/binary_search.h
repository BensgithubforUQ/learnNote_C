#pragma once
#include "vector_base.h"
#include <string>
using namespace std;

//binary_search 
//二分查找
/*查找指定元素，存在返回true，不存在返回false*/
//注意，在无序序列中不可用！！！！！！！！只能再set，map中使用，或者使用用排序完的其他容器中使用，还要注意升序降序

void binary_search_test() {
	vector<int>v1;
	constructVectorWithSize(v1, 50);
	printVector(v1);
	bool flag = binary_search(v1.begin(), v1.end(), 9);
	if (flag) {
		cout << "the element with value 9 is existing" << endl;
	}
	else {
		sort(v1.begin(), v1.end(), greater<int>());//greater就是自己写的那个descending
		printVector(v1);
		flag = binary_search(v1.begin(), v1.end(), 9, greater<int>());//注意，他这个默认搜索的，还是默认的升序排序
		//如果是降序，还要给个关系仿函数来定义一下查找规则。
		if (flag) {
			cout << "after sort, the element with value 9 is found" << endl;
		}
		else {
			cout << "the element with value 9 is not existing" << endl;
		}
	}
	
}