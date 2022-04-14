#pragma once
#include <iostream>
#include <string>
using namespace std;

class person
{
public:
	person();
	person(string name, int age, string addr);
	~person();
	void showInfo();
private:
	string name;
	int age;
	string* address;

};
