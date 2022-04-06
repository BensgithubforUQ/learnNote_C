#include "boss.h"

void Boss::showPersonalInfo() {
	cout << "老板工号:" << this->w_person_id << endl;
	cout << "老板姓名:" << this->w_name << endl;
	cout << "岗位简介:" << this->getBossInfo() << endl;
	cout << "岗位名称:" << "公司老板" << endl;
	cout << endl;
}

string Boss::getBossInfo() {
	return "公司老板，管理公司所有事物";
}

Boss::Boss(string n, int id, int d_id) {
	if (d_id != 0) {
		cerr << "公司老板的部门编号必须为0" << endl;
	}
	else {
		this->w_name = n;
		this->w_person_id = id;
		this->w_department_id = d_id;

	}
}

Boss::Boss() {

}

Boss::~Boss() {

}
