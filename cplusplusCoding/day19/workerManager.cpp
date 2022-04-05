#include "workerManager.h"

WorkerManager::WorkerManager() {//构造函数

}

WorkerManager::~WorkerManager() {//析构函数

}

void WorkerManager::show_Menu() {//显示菜单
	cout << "欢迎使用职工管理系统" << endl;
	cout << "0.退出职工管理系统" << endl;
	cout << "**1.增加职工信息**" << endl;
	cout << "**2.显示职工信息**" << endl;
	cout << "**3.删除离职职工**" << endl;
	cout << "**4.修改职工信息**" << endl;
	cout << "**5.查找职工信息**" << endl;
	cout << "6.排序打印职工信息" << endl;
	cout << "**7.清空所有数据**" << endl;
	cout << endl;
}

void WorkerManager::exit_Menu() {
	cout << "期待下次使用，再见" << endl;
	system("pause");
	exit(0);
}