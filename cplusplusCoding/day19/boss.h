#pragma once
#include "worker.h"

class Boss : public AbstractWorker {
public:
	Boss(string n, int id, int d_id);
	~Boss();
	void showPersonalInfo();
	string getBossInfo();
};