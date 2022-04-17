#pragma once
#include <iostream>
#include <string>
using namespace std;

class Person{
public:
	Person();
	Person(string n, int a, double h);
	~Person();
	void showInfo() const;
	void operator=(Person& p);
	int getAge() const;
	double getheight() const;
private:
	string p_name;
	int p_age;
	double p_height;
};

