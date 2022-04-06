#pragma once
#include "worker.h"

class Manager : public AbstractWorker {
public:
	Manager();
	Manager(string n, int id, int d_id);
	~Manager();
	void showPersonalInfo();
	string getDepartmentInfo();
	string getJobInfo();
};