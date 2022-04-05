#pragma once
#include "worker.h"
//class AbstractWorker {//职工抽象类
//public:
//	//AbstractWorker();
//	virtual ~AbstractWorker();
//
//	virtual void showPersonalInfo() = 0; //显示个人信息的纯虚函数
//	virtual void getDepartmentID();
//
//
//	int w_person_id; //职工工号id
//	string w_name;//职工名
//	int w_department_id;//职工部门ID
//	string w_job_define;//职工职位介绍
//	string w_job_name;//职工职位名称
//};

//普通雇员类
class Employee : public AbstractWorker {
public:
	Employee(string n,int id,int d_id);
	~Employee();
	void showPersonalInfo();
	string getDepartmentInfo();
	string getJobInfo();
};