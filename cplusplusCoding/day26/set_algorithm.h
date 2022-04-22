#pragma once
#include "vector_base.h"
#include <string>

using namespace std;

void set_intersection_test() {
	//求两个容器的交集
	vector<int>v1, v2, v3;
	
	constructVectorWithSize(v1,10);

	constructVectorWithSize(v2,10);

	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	printVector(v1);
	printVector(v2);
	v3.resize(min(v1.size(), v2.size()));//取小智

	vector<int>::iterator itEnd_intersection = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
	//返回个迭代器的位置，这个位置是交叠部分的末尾
	//注意，ser_interaction也只能对已经排序的容器使用
	printVector(v3);
	for (vector<int>::iterator it = v3.begin(); it != itEnd_intersection; it++) {
		cout << *it << " ";
	}
	cout << endl;
	//或者，直接裁剪***************************************************************************************
	//注意，这里还要整个收尾，因为set_intersection算出来的intersection的容量大小
	//小于或者等比较小的容器的大小，因此可能会出现末尾填充0的情况
	//因为set_intersection是对排序过的算法进行计算，因此这里知道是升序排列，所以可以resize
	//这里只需要计算容器中有多少个0，取较小值，然后用resize删除末尾的0
	int count_zero = min(count(v1.begin(),v1.end(),0), count(v1.begin(), v1.end(), 0));
	count_zero += count(v3.begin(), v3.end(), 0); //计算v3中有多少是默认补充的0
	v3.resize(v3.size() - count_zero);
	printVector(v3);
	
}

//这玩意儿
void set_union_test() {
	vector<int>v1, v2, v3;

	constructVectorWithSize(v1, 10);

	constructVectorWithSize(v2, 10);

	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	printVector(v1);
	printVector(v2);
	//并集最特殊的情况，是两个容器一模一样，这时候应该是size相加
	v3.resize(v1.size() + v2.size());
	auto itEnd_union = set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
	//打印一下看看
	printVector(v3);
	for_each(v3.begin(), itEnd_union,PrintInt_functor());
	//也可以resize，

}

void set_difference_test() {
	vector<int>v1, v2, v3,v4;

	constructVectorWithSize(v1, 10);

	constructVectorWithSize(v2, 10);

	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	printVector(v1);
	printVector(v2);
	//差集最特殊的情况也是size相加
	v3.resize(v1.size() + v2.size());
	v4.resize(v1.size() + v2.size());
	auto itEnd_difference_base_v1 = set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
	//set_difference是基于第一个容器的
	auto itEnd_difference_base_v2 = set_difference(v2.begin(), v2.end(), v1.begin(), v1.end(), v4.begin());
	//打印一下看看
	printVector(v3);
	printVector(v4);
	//for_each(v3.begin(), itEnd_difference_base_v2, PrintInt_functor());
	//也可以resize，
	//这里有坑，以后在注意吧

}