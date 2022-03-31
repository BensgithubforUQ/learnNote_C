#pragma once
#include "myHead.h"

class Fruit {
public:
	//构造函数
	Fruit();
	Fruit(string color);
	Fruit(const Fruit &f);//必须是const，因为是初始化，不能改变传进来的值
	//然后还必须是引用
	//析构函数
	~Fruit();
	void getColor();
private:
	string color;
};