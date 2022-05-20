#pragma once
#include "Person.h"

class Judges :public Person {
public:
	Judges();
	Judges(string n,int a,string gen);
	void showInfo();
	void add_grade(Grade &g);
	double return_final_grade();
	~Judges();
};

