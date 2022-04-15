#include <iostream>
#include "Candidate.h"
#include "Judges.h"
#include "Grade.h"
#include <deque>
#include <string>
#include <vector>
/*一点简单的复习，包括虚函数，多态，封装，继承*/
/*然后就是deque和vector的一些简单应用的复习*/
void evaluate(Person* c, Person* j, double grade, Grade &g) {
	g.name_judges = j->p_name;
	g.name_candidates = c->p_name;
	g.grade = grade;
	cout << "成功将评委" << g.name_judges << "给参赛者" << 
		g.name_candidates << "打的" << g.grade << "分录入" << endl;
}

int main() {
	Person* c1, * c2, * c3, * c4, * c5;
	c1 = new Candidate("赵一", 21, "男");
	c2 = new Candidate("钱二", 22, "女");
	c3 = new Candidate("孙三", 23, "男");
	c4 = new Candidate("李四", 24, "女");
	c5 = new Candidate("周五", 25, "男");
	vector<Person*>c_v;
	c_v.push_back(c1);
	c_v.push_back(c2);
	c_v.push_back(c3);
	c_v.push_back(c4);
	c_v.push_back(c5);
	Person* j1, * j2, * j3, * j4, * j5;
	j1 = new Judges("轩辕", 31, "男");
	j2 = new Judges("神农", 32, "男");
	j3 = new Judges("颛顼", 33, "男");
	j4 = new Judges("女娲", 34, "女");
	j5 = new Judges("伏羲", 35, "男");
	vector<Person*>j_v;
	j_v.push_back(j1);
	j_v.push_back(j2);
	j_v.push_back(j3);
	j_v.push_back(j4);
	j_v.push_back(j5);
	int g_1 = 1, g_2 = 1;
	for (auto c : c_v) {
		for (auto j : j_v) {
			Grade g;
			evaluate(c, j, g_2*g_1,g);
			c->grade.push_back(g);
			j->grade.push_back(g);
		    ++g_2;
		}
		++g_1;
	}
	for (auto c : c_v) {
		c->showInfo();
		cout << "最终得分：" << (double)c->return_final_grade() << endl<< endl;
	}
	for (auto j : j_v) {
		j->showInfo();
	}
	return 0;
}