#include <iostream>
#include <string>
#include "stl_class.h"
#include "predicate.h"
#include "arithmetic_functor.h"
#include "relation_functor.h"
#include "logic_functor.h"
using namespace std;

/*stl函数对象
重载操纵调用操作符的类，本质是个类，其对象称为函数对象
但是使用的时候很像函数，所以叫仿函数*/
/*
1.可以有参数，可以有返回值，
2.超出普通函数的概念，可以拥有自己的状态
3.函数对象可以作为参数进行传递
*/

/*返回类型为bool的仿函数成为谓词
operator()接受一个参数称为一元谓词
operator()接受两个参数称为二元谓词*/

/*内建函数对象
算术仿函数
关系仿函数
逻辑仿函数

这些仿函数所产生的对象，用法和一般函数完全相同
使用内建函数对象，需要引入头文件#include<functional>*/

int main() {
	/*test0();
	test1();
	test2();
	predicate0();*/
	//predicate1();
	//test_negate(); //内建函数对象，算术仿函数，一元运算，negate，取反
	//test_plus();//内建函数对象，算术仿函数，二元运算，plus，取反
	//关系仿函数
	//test_greater();
	test_logical_not();
;	return 0;
}