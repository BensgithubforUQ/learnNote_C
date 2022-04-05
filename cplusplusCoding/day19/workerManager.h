#pragma once//防止头文件重复包含
#include <iostream>
#include <string>
#include <fstream>
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
private:

};