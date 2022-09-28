#ifndef PRODUCER_H
#define PRODUCER_H
#include "person.h"

/******************
* class : person的子类 hamburgerMaker
* value :
* private:
*	_stat_int_PersonAmount： 对象计数(继承)
*	_int_handleCount： 对象每次能够操作的专门对象的个数。(继承)
******************/
class hamburgerMaker : public Person {
public:
	~hamburgerMaker()
	{

	}

	hamburgerMaker(int handleCount) 
	{
		this->set_int_handleCount(handleCount);
		this->personType = m_hamburgerMaker;
	}

protected:
private:
	
};

#endif // !PRODUCER_H
