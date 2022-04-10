#include "person.h"

person::person() {

}

person::person(string n, int a, string addr) {
	this->name = n;
	this->age = a;
	cout << addr.size() << endl;
	this->address = new string[addr.size()];
	*(this->address) = addr;
	cout << (int)&addr << endl;
	cout << (int)&(this->address) << endl;
	cout << (int)&age << endl;
	cout << (int)(this->address) << endl;
}

person::~person() {
//	if (this->address != NULL) {
//		delete this->address;
//		this->address = NULL;
//}
}

void person::showInfo() {
	cout << this->name << " " << this->age << " " << *(this->address) << endl;
}