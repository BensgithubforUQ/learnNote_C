#pragma once
#include "myHead.h"
#include "Phone.h"
class Person
{
public:
	Person();
	Person(int a,int h,Phone p_P);
	Person(const Person &p); 
	~Person();//析构函数，通常用于将堆区开辟的数据释放。
	int getAge();
    int getHeight();
	void showP();//展示对象的类属性
private:
	int age;
	int* m_height;//身高，用指针是因为想要在堆区储存这个数据
	Phone p_Phone;//手机类
};

