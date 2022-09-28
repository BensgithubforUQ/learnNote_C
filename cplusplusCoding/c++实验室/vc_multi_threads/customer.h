#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "person.h"


/******************
* class : Customer
* value :
*	int _consume_product; 消耗的产品种类
*	static int _statCusumCount; 消费者一共消耗了多少产品
******************/
class Customer :public Person {
public:
	virtual ~Customer()
	{
	}

	Customer(int consume_product, int handleCount) :_consume_product(consume_product)
	{
		this->set_int_handleCount(handleCount);
	}

	static void calculateCustomerAmount(Customer & _c) {
		_statCusumCount += getHandleCount(_c);
	}

	static int get_statCusumCount() {
		return  _statCusumCount;
	}
protected:
private:
	int _consume_product;
	static int _statCusumCount;
};

int Customer::_statCusumCount = 0;
#endif // !CUSTOMER_H
