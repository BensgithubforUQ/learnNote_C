#ifndef PRODUCER_H
#define PRODUCER_H
#include "person.h"

/******************
* class : person的子类 hamburgerMaker
* value :
*	_stat_int_PersonAmount： 对象计数
*	_int_handleCount： 对象每次能够操作的专门对象的个数。
******************/
class hamburgerMaker : Person {
public:
	~hamburgerMaker()
	{

	}

	hamburgerMaker(int handleCount) 
	{
		this->set_int_handleCount(handleCount);
	}

protected:
private:

};

#endif // !PRODUCER_H
