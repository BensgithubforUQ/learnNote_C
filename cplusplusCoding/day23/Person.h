#pragma once
#include <iostream>
#include <string>
using namespace std;

class Person{
public:
	Person();
	Person(string n, int a, double h);
	~Person();
	void showInfo();
	void operator=(Person& p);
	int getAge();
	double getheight();
private:
	string p_name;
	int p_age;
	double p_height;
};

