#pragma once
#include "Person.h"

class Candidate:public Person{
public:

	Candidate();
	Candidate(string n, int a, string gen);
	void showInfo();
	void add_grade(Grade& g);
	double return_final_grade();
	~Candidate();
};

