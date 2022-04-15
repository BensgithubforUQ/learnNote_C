#pragma once
#pragma once
#include <iostream>
#include <queue>
using namespace std;

//队列容器
//队列是先进先出的数据结构，有两个出口，允许一端新增数据，另外一端出数据
//只能读队头front和队尾back的数据,因此也不可遍历，
//进数据被称为入队push，出数据被称为出队pop

void queue_test0() {
	//初始化
	queue<int> q1,q3;
	//赋值
	if (q1.empty()) {//是否为空？
		for (int i = 0; i < 10; i++) {
			q1.push(i);
			cout << "front为：" << q1.front();
			cout << " back为：" << q1.back() << endl;
		}
	}
	
	//拷贝构造
	queue<int>q2(q1);
	q3 = q2;
	cout << "size of queue q3: " << q3.size() << endl;

	while (!q3.empty()) {
		cout << "front为：" << q3.front();
		cout << " back为：" << q3.back() << endl;//先进先出的体现
		q3.pop();
	}
}