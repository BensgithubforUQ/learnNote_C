#include "Judges.h"

Judges::Judges() {
	//默认构造，不初始化
	cout << "默认构造一个judge" << endl;
}
Judges::Judges(string n, int a, string gen) {
	cout << "有参构造一个judge" << endl;
	this->p_name = n;
	this->p_age = a;
	this->p_gender = gen;
	this->grade.resize(0);//整个初始化
}
void Judges::showInfo() {
	cout << "姓名： " << this->p_name << endl;
	cout << "角色： " << "评委" << endl;
	cout << "年龄： " << this->p_age << endl;
	cout << "性别： " << this->p_gender << endl;
	cout << "打印该评委的评分" << endl;
	for (auto i : this->grade) {
		cout << i.name_candidates << " " << i.grade << " " << i.name_judges << endl;
	}
	cout << endl;
}
void Judges::add_grade(Grade& g) {
	this->grade.push_back(g);
	cout << "成功添加一组数据" << endl;
}
Judges::~Judges() {
	cout << "无堆区数据，默认析构" << endl;
}

double Judges::return_final_grade() {
	return 0;
}