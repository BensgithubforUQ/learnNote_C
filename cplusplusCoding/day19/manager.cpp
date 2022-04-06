#include "manager.h"

void Manager::showPersonalInfo() {
	cout << "经理工号:" << this->w_person_id << endl;
	cout << "经理姓名:" << this->w_name << endl;
	cout << "部门编号:" << this->w_department_id << endl;
	cout << "岗位简介:" << this->getJobInfo() << endl;
	cout << "岗位名称:" << this->getDepartmentInfo() << endl;
	cout << endl;
}

string Manager::getDepartmentInfo() {
	return "经理";
}

string Manager::getJobInfo() {
	return "完成上司交代的任务，管理下属";
}

Manager::Manager(string n, int id, int d_id) {
	this->w_name = n;
	this->w_person_id = id;
	this->w_department_id = d_id;

}
Manager::Manager() {

}

Manager::~Manager() {

}
