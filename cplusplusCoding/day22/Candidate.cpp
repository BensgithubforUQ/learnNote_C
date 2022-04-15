#include "Candidate.h"
#include <deque>
#include <algorithm>

Candidate::Candidate() {
	//默认构造，不初始化
	cout << "默认构造一个judge" << endl;
}
Candidate::Candidate(string n, int a, string gen) {
	cout << "有参构造一个judge" << endl;
	this->p_name = n;
	this->p_age = a;
	this->p_gender = gen;
	this->grade.resize(0);//整个初始化
}
void Candidate::showInfo() {
	cout << "姓名： " << this->p_name << endl;
	cout << "角色： " << "参赛者" << endl;
	cout << "年龄： " << this->p_age << endl;
	cout << "性别： " << this->p_gender << endl;
	cout << "打印该参赛者的得分" << endl;
	for (auto i : this->grade) {
		cout << i.name_candidates << " " << i.grade << " " << i.name_judges << endl;
	}
}
void Candidate::add_grade(Grade& g) {
	this->grade.push_back(g);
	cout << "成功添加一组数据" << endl;
}
Candidate::~Candidate() {
	cout << "无堆区数据，默认析构" << endl;
}

double Candidate::return_final_grade() {
	deque<double> d_grade;
	for (auto c : this->grade) {
		d_grade.push_back(c.grade);
	}
	sort(d_grade.begin(),d_grade.end());
	d_grade.pop_front();
	d_grade.pop_back();
	double final_grade = 0.0;
	for (deque<double>::const_iterator it = d_grade.begin(); it != d_grade.end(); it++) {
		final_grade += *it;
	}
	final_grade = final_grade / d_grade.size();
	return final_grade;
}