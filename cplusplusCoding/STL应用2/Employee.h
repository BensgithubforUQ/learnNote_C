#pragma once
#include <iostream>
#include <string>
using namespace std;

class Employee {
public:
	string name;
	int salary;

	Employee();
	Employee(string n,int s);
	void showInfo();
	~Employee();
};