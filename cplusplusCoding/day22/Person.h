#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Grade.h"
using namespace std;

class Person{//Ðéº¯ÊýÀà
public:
	virtual void showInfo() = 0;
	virtual double return_final_grade() = 0;
public:
	string p_name;
	int p_age;
	string p_gender;
	vector<Grade> grade;
};

