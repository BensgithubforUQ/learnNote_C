#include <iostream>
#include <string>
#include "myHead.h"
#include <vector>
using namespace std;

//int main() {
//	struct student stu1;
//	stu1.name = "张三";
//	stu1.age = 26;
//	stu1.grade = 95.0;
//	struct student stu2 {
//		"李四", 19, 96.0
//	};
//	struct student stu3;
//	stu3.name = "王五" ;
//	stu3.age = 24;
//	stu3.grade = 97.5;
//	struct student stu4[5]{
//		"陆左", 31, 31.0,
//		"陆朵朵",5,99.0,
//		"陆妖妖",9,100.0,
//		"肖克明",29,94.0,
//		"虎皮猫",200,120.0
//	};
//	printStructStudent(stu1);
//	printStructStudent(stu2); 
//	printStructStudent(stu3);
//
//	cout << endl;
//	//结构体数组
//	struct student studentArray[] = { stu1,stu2,stu3,{"赵六",30,99.0}};
//	studentArray[2].age = 31;
//	studentArray[2].grade = 100.0;
//	auto len = sizeof(studentArray) / sizeof(studentArray[0]);
//	cout << "size :" <<len<< endl;
//	for (auto i : studentArray) {
//		printStructStudent(i);
//	}
//
//	//结构体指针
//	struct student* p = &stu1; //用一个指针p，指向stu1;
//	cout << endl;
//	cout << "指针->打印" << endl;
//	//cout << p->name << " 年龄 " << p->age << " 成绩 " << p->grade << endl;
//	printStructStudent2(&stu1);
//
//	//利用指针访问结构体数组p->name
//	cout << endl;
//	cout << "利用指针访问结构体数组" << endl;
//	struct student* p1 = studentArray;
//	for (int i = 0; i < len; i++) {
//		printStructStudent2(p1 + i);
//	}
//
//	//结构体嵌套结构体
//	cout << endl;
//	cout << "结构体嵌套结构体" << endl;
//	struct teacher t[2];
//	t[0].name = "管仲";
//	t[0].age = 100;
//	for (int i = 0; i < 3; i++) {
//		t[0].stu.push_back(studentArray[i]);
//	}
//	t[1].name = "乐毅";
//	t[1].age = 99;
//	t[1].stu.push_back(studentArray[3]);
//	//cout << "请继续为乐毅老师输入学生信息" << endl;
//	//inputStructStudent(t+1);
//	struct teacher* pt = t;
//	int len1 = sizeof(t) / sizeof(t[0]);
//	//printStructTeacher(pt, len1);
//
//	inputStructStudent2(&t[1], stu4, 5);
//	printStructTeacher(pt, len1);
//
//
//	return 0;
//}