#include "myHead.h"

void printStructStudent(struct student stu) {
	cout << "结构体中对象的姓名" << stu.name << "年龄" << stu.age << "成绩" << stu.age << endl;
}
//将函数中的形参改为指针，可以降低内存空间消耗，并且可以不用每次都复制一个输入的副本，而一个指针只占四个内存空间。
//因为值传递进函数是重新生成一个副本，并不对原对象进行操作。那么结构体有多大，副本就有多大，极大的消耗了内存空间。
void printStructStudent2(struct student *stu) {
	cout << "结构体中对象的姓名" << stu->name << "年龄" << stu->age << "成绩" << stu->age << endl;
}

//打印teacher对象
void printStructTeacher(struct teacher* t,int len) {
	for (int i = 0; i < len; i++) {
		cout << (t + i)->name << " 年龄 " << (t + i)->age << endl;
		auto beg = (t + i)->stu.begin();
		while (beg != (t + i)->stu.end()) {
			cout << beg->name << " 年龄 " << beg->age << " 成绩 " << beg->grade << endl;
			beg++;
		}
	}
}

//向"teacher"对象里面加“student”的数据
void inputStructStudent(struct teacher* t) {
	string name;
	int age;
	float grade;
	cin >> name >> age >> grade;
	t->stu.push_back({ name,age,grade });
}

void inputStructStudent2(struct teacher* t, struct student *s,int len) {
	for (int i = 0; i < len; i++) {
		t->stu.push_back({ (s+i)->name,(s + i)->age,(s + i)->grade });
	}
}