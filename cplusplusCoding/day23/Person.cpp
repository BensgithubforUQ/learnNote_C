#include "Person.h"

Person::Person() {
	cout << "calling default constructor" << endl;
}

Person::Person(string n, int a, double h) {
	this->p_name = n;
	this->p_age = a;
	this->p_height = h;
	cout << "calling copy constructor" << endl;
}

Person::~Person() {
	cout << "calling Destructor" << endl;
}


void Person::showInfo() const {
	cout << "姓名 " << this->p_name << " 年龄 " << this->p_age << " 身高 " << this->p_height << endl;
}

void Person::operator=(Person& p) {
	this->p_name = p.p_name;
	this->p_age = p.p_age;
	this->p_height = p.p_height;
}

int Person::getAge() const {
	return this->p_age;
}
double Person::getheight() const {
	return this->p_height;
}