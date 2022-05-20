#include "employee.h"

void Employee::showPersonalInfo() {
	cout << "员工工号:" << this->w_person_id << endl;
	cout << "员工姓名:" << this->w_name << endl;
	cout << "部门编号:" << this->w_department_id << endl;
	cout << "岗位简介:" << this->getJobInfo() << endl;
	cout << "岗位名称:" << this->getDepartmentInfo() << endl;
	cout << endl;
}

string Employee::getDepartmentInfo() {
	return "普通员工";
}

string Employee::getJobInfo() {
	return "完成经理交给的任务";
}

Employee::Employee(string n, int id, int d_id) {
	this->w_name = n;
	this->w_person_id = id;
	this->w_department_id = d_id;

}
Employee::Employee() {

}

Employee::~Employee() {

}
