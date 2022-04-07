#pragma once//防止头文件重复包含
#include <iostream>
#include <string>
#include <fstream>
#include "worker.h"
#include <vector>
using namespace std;

class WorkerManager {
public:
	//构造函数
	WorkerManager();
	//析构函数
	~WorkerManager();
	//功能性函数
		//显示菜单
	void show_Menu();
	void exit_Menu();
	void save_file();
	void addEmployee();
	int get_worker_number();
	void initial_Worker();
	void show_WorkerInfo();
	void search_Worker();
	int search_Worker_withId();
	int search_Worker_withName(vector<int> id_vector);
	int isExist(string name, vector<int> id_vector);
	int isExist(int id);
	void delete_Worker();
	void confirm_delete(int id);
	void change_worker_info();
	int check_same_id(int id);
	void sort_Worker();
	void delete_all_data();
private:
	int worker_size;
	AbstractWorker** worker_array;
	bool fileIsEmpty;
};