#include "Employee.h"

Employee::Employee() {
	cout << "Ä¬ÈÏ¹¹Ôì" << endl;
}


Employee::Employee(string n,int s) {
	this->name = n;
	this->salary = s;
}

void Employee::showInfo() {
	cout << "name: " << this->name << " salary: " << this->salary << endl;
}

Employee::~Employee() {

}