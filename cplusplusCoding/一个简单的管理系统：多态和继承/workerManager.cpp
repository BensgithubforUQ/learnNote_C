#include "workerManager.h"
#include "boss.h"
#include "employee.h"
#include "manager.h"
#include <vector>
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
		//删除堆区的每个职工对象，然后还需要删除堆区这个数组的指针、
		for (int i = 0; i < this->worker_size; i++) {
			delete this->worker_array[i];
			this->worker_array[i] = NULL;
		}
		//删除数组指针
		delete[] this->worker_array;
		this->worker_array = NULL;
		this->worker_size = 0;
		this->fileIsEmpty = true;
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

int WorkerManager::check_same_id(int id) {
	for (int i = 0; i < this->worker_size; i++) {
		if (id == this->worker_array[i]->w_person_id) {
			cout << "id重复，请重新输入" << endl;
			return 1;
		}
	}
	return 0;
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
			 do
			 {
				 cin >> id;
			 } while (check_same_id(id));
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
				 cout << "警告，初始化分类为普通员工" << endl;
				 worker = new Employee(name, id, d_id);
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
	ofs.open(fileName, ios::out);
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
int WorkerManager::isExist(string name, vector<int> id_vector) {
	bool flag = false;
	int id;
	for (int i = 0; i < this->worker_size; i++) {
		if (this->worker_array[i]->w_name == name) {
			cout << "存在该职工" << endl;
			flag = true;
			id_vector.push_back(i);
			cout << "工号：" << this->worker_array[i]->w_person_id << " "
				<< "姓名： " << this->worker_array[i]->w_name << " "
				<< "部门编号： " << this->worker_array[i]->w_department_id << endl;
			id = i;
		}
	}
	if (flag) {
		return id;
	}
	else {
		cout << "职工不存在" << endl;
		return -1;
	}
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

int WorkerManager::search_Worker_withName(vector<int> id_vector) {
	cout << "请输入名字" << endl;
	string name;
	cin >> name;
	int id = this->isExist(name, id_vector);
	if (id != -1) {
		for (int i : id_vector) {
			cout << "职工信息为：" << endl;
			cout << "工号：" << this->worker_array[i]->w_person_id << " "
				<< "姓名： " << this->worker_array[i]->w_name << " "
				<< "部门编号： " << this->worker_array[i]->w_department_id << endl;
		}

	}
	return id;
}

int WorkerManager::search_Worker_withId() {
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
	return id;
}

void WorkerManager::search_Worker() {
	cout << "请选择你要如何查询职工" << endl
		<< "1.根据名字查询" << endl
		<< "2.根据id查询" << endl;
	int choice;
	cin >> choice;
	if (choice == 1) {
		search_Worker_withId();
	}
	else if (choice == 2) {
		vector<int> id_vector;
		search_Worker_withName(id_vector);
	}
	system("pause");


	system("cls");
}
void WorkerManager::confirm_delete(int id) {
	cout << "真的要删除该职工的信息吗?是请输入Y/y，否则取消" << endl;
	char make_Sure;
	cin >> make_Sure;
	if (make_Sure == 'Y'|| make_Sure == 'y') {
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
		<< "1.根据id查询" << endl
		<< "2.根据名字查询" << endl;
	int choice;
	cin >> choice;
	if (choice == 1) {
		int id = search_Worker_withId();
		if (id != -1) {
			this->confirm_delete(id);
		}
	}
	else if (choice == 2) {
		vector<int> id_vector;
		int id = search_Worker_withName(id_vector);
		if (id != -1) {
			this->confirm_delete(id);
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::change_worker_info() {
	cout << "请选择你要如何查询职工" << endl
		<< "1.根据id查询" << endl
		<< "2.根据名字查询" << endl;
	int choice;
	cin >> choice;
	vector<int> id_vector;
	int id = 0;
	if (choice == 1) {
		id = search_Worker_withId();
	}
	else if (choice == 2) {
		
		id = search_Worker_withName(id_vector);
	}
	if (id != -1) {
			cout << "请输入修改后的员工姓名：" << endl;
			getchar();//停止一下，因为要输入一个回车
			getline(cin, this->worker_array[id]->w_name);
			cout << "请输入修改后的员工部门编号：" << endl;
			int d_id;
			cin >> d_id;
			this->worker_array[id]->w_department_id = d_id;

		
		this->save_file();
		cout << "修改成功......" << endl;
	}
	system("pause");
	system("cls");
}

void WorkerManager::sort_Worker() {
	if (this->fileIsEmpty) {
		cout << "空文件" << endl;
	}
	else {
		for (int i = 0; i < this->worker_size; i++) {
			for (int j = i + 1; j < this->worker_size; j++) {
				if (this->worker_array[i]->w_person_id > this->worker_array[j]->w_person_id) {
					int temp_id;
					int temp_d_id;
					string temp_name;
					temp_id = this->worker_array[i]->w_person_id;
					temp_d_id = this->worker_array[i]->w_department_id;
					temp_name = this->worker_array[i]->w_name;
					this->worker_array[i]->w_person_id = this->worker_array[j]->w_person_id;
					this->worker_array[i]->w_department_id = this->worker_array[j]->w_department_id;
					this->worker_array[i]->w_name = this->worker_array[j]->w_name;
					this->worker_array[j]->w_person_id = temp_id;
					this->worker_array[j]->w_department_id = temp_d_id;
					this->worker_array[j]->w_name = temp_name;

				}
			}
		}
	}
	this->save_file();
	cout << "排序完毕" << endl;
	system("pause");
	system("cls");
}

void WorkerManager::delete_all_data() {
	cout << "确定删除？输入Y/y，其他取消" << endl;
	char confirm;
	cin >> confirm;
	if (confirm == 'y' || confirm == 'Y') {
		ofstream ofs(fileName,ios::trunc);//先把文件删除重新建个空的
		ofs.close();
		if (this->worker_array != NULL) {
			//相当于主动析构
			for (int i = 0; i < this->worker_size; i++) {
				delete this->worker_array[i];
				this->worker_array[i] = NULL;
			}
			//删除数组指针
			delete[] this->worker_array;
			this->worker_array = NULL;
			this->worker_size = 0;
			this->fileIsEmpty = true;
			cout << "数据已经全部删除完毕" << endl;
		}
		else {
			cout << "文件为空，不可删除" << endl;
		}
	}
	system("pause");
	system("cls");
}