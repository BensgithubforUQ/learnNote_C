#pragma once
#include "myHead.h"
class Phone
{
public:
	Phone();
	Phone(const Phone& p);
	Phone(int n, string t);
	~Phone();
	int getNum();
	string getStr();
	void showPhone();
private:
	int number;
	string type;
};

