#pragma once
#include <iostream>
#include <stack>
using namespace std;

/*栈容器*/
/*栈，是先进后出的。*/
/*先进的数据沉到栈底，后进的数据浮在栈顶，入栈为push，出栈为pop
栈是不允许遍历的，只有栈顶元素才能被访问到。而遍历是一个非质变的操作，如果一个个出栈则不为遍历*/
/*栈虽然不能遍历，但是栈可以进行长度判断操作，比如可以返回长度和是否为空*/


void stack_test0() {
	//构造1
	stack<int> s1,s3;
	//是否为空
	if (s1.empty()) {
		for (int i = 0; i < 10; i++) {
			s1.push(i);//入栈操作
		}
	}
	//拷贝构造
	stack<int>s2(s1);
	s3 = s2;
	
	while (!s3.empty()) {
		cout << "栈的大小： " << s3.size() << endl; //查看栈的大小
		cout << "查看栈顶元素: " << s3.top() << endl; //查看栈顶元素
		s3.pop(); //出栈操作
	}
}