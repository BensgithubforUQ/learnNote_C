#include "workerManager.h"
#include "boss.h"
#include "employee.h"
#include "manager.h"
constexpr auto fileName = "workermanager_data.txt";

WorkerManager::WorkerManager() {//构造函数
	//文件不存在的情况
	ifstream ifs;
	ifs.open(fileName, ios::in);
	if (!ifs.is_open()) {
		cerr << "file is not existing" << endl;
		//初始化属性
		this->worker_array = NULL;
		this->worker_size = 0;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	else {
		char checkIfIsBlank;
		ifs >> checkIfIsBlank;
		if (ifs.eof()) {
			cout << "数据文件为空" << endl;
			this->worker_array = NULL;
			this->worker_size = 0;
			this->fileIsEmpty = true;
			ifs.close();
		}
		else {
			
			int worker_number = this->get_worker_number();
			this->worker_size = worker_number;
			cout << "数据文件存在，正常运行程序,有：" <<this->worker_size<<"个员工" << endl;
			
			this->initial_Worker();
		}
	}

}

WorkerManager::~WorkerManager() {//析构函数
	//析构，堆区数据，手动开辟，手动释放，养成好习惯
	if (this->worker_array != NULL) {
		delete[] this->worker_array;
		this->worker_array = NULL;
		cout << "成功析构workermanager对象" << endl;
	}
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

void WorkerManager::addEmployee() {
	cout << "请输入想要增加的职工的个数" << endl;
	int addNum = 0;
	cin >> addNum;

	if (addNum > 0) {
		int newSize = addNum + this->worker_size;//计算新的，需要在堆区开辟的空间的大小
		//开辟新空间
		 AbstractWorker **new_worker_array = new  AbstractWorker* [newSize+8];
		 if (this->worker_array != NULL) {
			 for (int i = 0; i < this->worker_size;i++) {
				 new_worker_array[i] = worker_array[i];
			 }
		 }
		 for (int j = 0; j < addNum; j++) {
			 int id;
			 string name;
			 int d_id;
			 cout << "请输入第 " << j + 1 << "个用户的编号" << endl;
			 cin >> id;
			 cout << "请输入第 " << j + 1 << "个用户的名字" << endl;
			 cin >> name;
			 cout << "请选择第 " << j + 1 << "个用户的岗位" << endl;
			 cout << "0,boss，1,manager,2,employee" << endl;
			 cin >> d_id;

			 AbstractWorker* worker = NULL;
			 switch (d_id)
			 {
			 case 0:
				 worker = new Boss(name, id, d_id);
				 break;
			 case 1:
				 worker = new Manager(name, id, d_id);
				 break;
			 case 2:
				 worker = new Employee(name, id, d_id);
				 break;
			 default:
				 break;
			 }
			 new_worker_array[this->worker_size + j] = worker;
		 }
		 //释放原有的空间
		 delete[] this->worker_array;
		 //更改新空间的指向
		 this->worker_array = new_worker_array;
		 //更新新空间的大小（职工人数）
		 this->worker_size = newSize;
		 this->save_file();
		 this->fileIsEmpty = false;
		 cout << "成功添加了：" << newSize << "名新职工，现有员工总数为：" << this->worker_size << endl;
	}
	else {
		cout << "输入有误，请输入大于零的数字" << endl;

	}
	system("pause");
	system("cls");
}

void WorkerManager::save_file() {
	ofstream ofs;//定义流对象
	//打开,用输出的模式打开，意思就是写文件
	ofs.open(fileName, ios::out|ios::trunc);
	//for循环，把记录的人输入到文件中
	for (int i = 0; i < this->worker_size; i++) {
		ofs << this->worker_array[i]->w_person_id << " "
		<< this->worker_array[i]->w_name<<" "
		<< this->worker_array[i]->w_department_id << endl;
	}
	ofs.close();
}	

int WorkerManager::get_worker_number() {
	ifstream ifs;
	ifs.open(fileName, ios::in);
	int id;
	string name;
	int d_id;
	int number = 0;
	while (ifs >> id && ifs >> name && ifs >> d_id) {
		number++;//统计人数
	}
	return number;
}

void WorkerManager::initial_Worker() {
	ifstream ifs;
	ifs.open(fileName, ios::in);
	this->worker_array = new AbstractWorker * [this->worker_size];//new个堆区空间
	int id, d_id;
	string name;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> d_id) {
		AbstractWorker* worker = NULL;
		if (d_id == 2) {
			worker = new Employee(name, id, d_id);
		}
		if (d_id == 0) {
			worker = new Boss(name, id, d_id);
		}
		if (d_id == 1) {
			worker = new Manager(name, id, d_id);
		}
		this->worker_array[index++] = worker;
	}
	ifs.close();
}

void WorkerManager::show_WorkerInfo() {
	if (this->fileIsEmpty == false) {
		cout << "一共有" << this->worker_size << "名职工" << endl;
		for (int i = 0; i < this->worker_size; i++) {
			cout << "工号：" << this->worker_array[i]->w_person_id << " "
				<< "姓名： " << this->worker_array[i]->w_name << " "
				<< "部门编号： " << this->worker_array[i]->w_department_id << endl;
		}
	}
	else {
		cout << "文件不存在，或者文件为空" << endl;
	}
	system("pause");
	system("cls");
}
int WorkerManager::isExist(string name) {
	for (int i = 0; i < this->worker_size; i++) {
		if (this->worker_array[i]->w_name == name) {
			cout << "存在该职工" << endl;
			return i;
		}
	}
	cout << "职工不存在" << endl;
	return -1;
}
int WorkerManager::isExist(int id) {
	for (int i = 0; i < this->worker_size; i++) {
		if (this->worker_array[i]->w_person_id == id) {
			cout << "存在该职工编号对应的职工" << endl;
			return i;
		}
	}
	cout << "职工不存在" << endl;
	return -1;
}
void WorkerManager::search_Worker() {
	cout << "请选择你要如何查询职工" << endl
		<< "1.根据名字查询" << endl
		<< "2.根据id查询" << endl;
	int choice;
	cin >> choice;
	if (choice == 1) {
		cout << "请输入名字" << endl;
		string name;
		cin >> name;
		int id = this->isExist(name);
		if (id != -1) {
			cout << "职工信息为：" << endl;
			cout << "工号：" << this->worker_array[id]->w_person_id << " "
				<< "姓名： " << this->worker_array[id]->w_name << " "
				<< "部门编号： " << this->worker_array[id]->w_department_id << endl;
		}
	}
	else if (choice == 2) {
		cout << "请输入编号" << endl;
		int search_id;
		cin >> search_id;
		int id = this->isExist(search_id);
		if (id != -1) {
			cout << "职工信息为：" << endl;
			cout << "工号：" << this->worker_array[id]->w_person_id << " "
				<< "姓名： " << this->worker_array[id]->w_name << " "
				<< "部门编号： " << this->worker_array[id]->w_department_id << endl;
		}
	}
	system("pause");
	system("cls");
}
void WorkerManager::confirm_delete(int id) {
	cout << "真的要删除该职工的信息吗?是请输入Y，否则取消" << endl;
	char make_Sure;
	cin >> make_Sure;
	if (make_Sure == 'Y') {
		this->worker_array[id] = this->worker_array[this->worker_size - 1];
		this->worker_array[this->worker_size - 1] = NULL;
		--this->worker_size;
		this->save_file();
	}
	else {
		cout << "取消删除";
		return;
	}
}
void WorkerManager::delete_Worker() {
	cout << "请选择你要如何查询职工" << endl
		<< "1.根据名字查询" << endl
		<< "2.根据id查询" << endl;
	int choice;
	cin >> choice;
	if (choice == 1) {
		cout << "请输入名字" << endl;
		string name;
		cin >> name;
		int id = this->isExist(name);
		if (id != -1) {
			cout << "职工信息为：" << endl;
			cout << "工号：" << this->worker_array[id]->w_person_id << " "
				<< "姓名： " << this->worker_array[id]->w_name << " "
				<< "部门编号： " << this->worker_array[id]->w_department_id << endl;
		}
		this->confirm_delete(id);
	}
	else if (choice == 2) {
		cout << "请输入编号" << endl;
		int search_id;
		cin >> search_id;
		int id = this->isExist(search_id);
		if (id != -1) {
			cout << "职工信息为：" << endl;
			cout << "工号：" << this->worker_array[id]->w_person_id << " "
				<< "姓名： " << this->worker_array[id]->w_name << " "
				<< "部门编号： " << this->worker_array[id]->w_department_id << endl;
		}
		this->confirm_delete(id);
	}
	system("pause");
	system("cls");
}
