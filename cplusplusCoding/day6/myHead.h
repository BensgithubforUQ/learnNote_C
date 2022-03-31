#pragma once
#include <iostream>
#include <string>
#include "myHead.h"
#include <vector>
using namespace std;


struct student {
	string name;
	int age;
	float grade;
};

struct teacher {
	string name;
	int age;
	vector<struct student> stu;
};

struct person {
	string addrName;
	int addrAge;
	string addrGender;
	vector<long long> addrNumber;
	string addrAddress;
	bool addrStarContacts;
};

struct address {
	vector<struct person> people;
	const int max = 10;
};

int add(int num1, int num2);
void swap(int* num1, int* num2);
void printArray(int* arr, int len);
int  getSizeOfArr(int* arr);
void popArr(int* arr, int len);

//结构体函数
void printStructStudent(struct student stu);
void printStructStudent2(struct student* stu);
void inputStructStudent(struct teacher* t);
void printStructTeacher(struct teacher* t, int len);
void inputStructStudent2(struct teacher* t, struct student* s, int len);

//通讯录增删查改印
int addAddress(struct address* ab, struct person* a);
//删
int delAddress(struct address* ab);
//查
int searchAddress(struct address* a);
//改
int changeAddress(struct address* abs);
//印
void printAddress(struct person a);
void printAddressList(struct address a);
//全删
int delAddressList(struct address* a);
//退
void exitAddressList();
void menu();

