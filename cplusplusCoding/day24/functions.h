#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include "Employee.h"
#include <map>
using namespace std;

#define planningDep 0
#define developDep 1
#define artDep 2

void addElement(vector<Employee> &v); //向vector容器中添加元素
void assignTask(vector<Employee>& v,multimap<int, Employee>&m); //给vector容器里面的员工分配任务
void showTaskGroup(const vector<Employee>& v);
void showTaskGroup( multimap<int,Employee> &m);
void department(multimap<int, Employee>& m, int i);//按部门打印，int参数输入的是key值
void showMapByTask(multimap<int, Employee>& m);//笼统的show函数。