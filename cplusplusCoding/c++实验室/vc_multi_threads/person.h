#pragma once

#include <iostream>

/******************
* class : person 生产者消费者模型基类
* value :
*	_stat_int_PersonAmount： 对象计数
*	_int_handleCount： 对象每次能够操作的专门对象的个数。
******************/
class Person {
	friend int getHandleCount(Person& _p)
	{
		return _p._int_handleCount;
	}
public:
	virtual ~Person()
	{
		//
		--_stat_int_PersonAmount;
	}

	/*default _int_handleCount = 1*/
	Person()
	{
		_int_handleCount = 1;
		++_stat_int_PersonAmount;
	}

	Person(int handleCount) : _int_handleCount(handleCount) {
		++_stat_int_PersonAmount;
	}

	Person(Person& _p)
	{
		this->_int_handleCount = _p._int_handleCount;
		++_stat_int_PersonAmount;
	}

	Person& operator =(Person& _p) {
		this->_int_handleCount = _p._int_handleCount;
		return *this;
	}


	void set_int_handleCount(int handleCount)
	{
		_int_handleCount = handleCount;
	}

	int get_int_handleCount() 
	{
		return _int_handleCount;
	}

	static int getPersonAmount()
	{
		return _stat_int_PersonAmount;
	}

	
protected:

private:
	static int _stat_int_PersonAmount;
	int _int_handleCount;
};

/*初始化person类的static int变量*/
int Person::_stat_int_PersonAmount = 0;

enum PRODUCT_TYPE
{
	hamburger = 1, lamian = 2, cookie = 3
};