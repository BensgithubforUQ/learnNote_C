#include "functions.h"

void addElement(vector<Employee> &v) {
	string nameSeed("abcdefghijklmnopqrstuvwxyz");
	srand((unsigned int)time(NULL));
	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "员工";
		name += nameSeed[i];
		Employee temp(name,rand()%10000+10000);//1w - 19999
		v.push_back(temp);
	}
}//向vector容器中添加元素

void assignTask(vector<Employee>& v, multimap<int, Employee>&m) {
	if (!v.empty()) {
		cout << "size of vector :" << v.size() << endl;
		for (vector<Employee>::const_iterator it = v.begin(); it != v.end(); it++) {
			//产生随机的部门编号
			int departmentId = rand() % 3 + 0;// 0 1 2
			//将编号和employee对象插入
			m.insert(make_pair(departmentId, *it));
		}
	}
	else {
		cout << "this vector is empty" << endl;
	}
} //给vector容器里面的员工分配任务

void showTaskGroup(const vector<Employee>& v) {
	if (!v.empty()) {
		cout << "size of vector :" << v.size() << endl;
		for (vector<Employee>::const_iterator it = v.begin(); it != v.end(); it++) {
			cout << "name: " << it->name << " salary: " << it->salary << endl;
		}
	}
	else {
		cout << "this vector is empty" << endl;
	}
	
}

void showTaskGroup( multimap<int, Employee>& m) {
	if (!m.empty()) {
		cout << "size of multimap :" << m.size() << endl;
		for (multimap<int, Employee>::iterator it = m.begin(); it != m.end(); it++) {
			cout << "key: "<<it->first 
				<< " name: " << it->second.name 
				<< " salary: " << it->second.salary << endl;
		}
	}
	else {
		cout << "this vector is empty" << endl;
	}
}


void department(multimap<int, Employee>& m, int i) {
	
	multimap<int, Employee>::iterator plan_it = m.find(i);
	int count_m = m.count(i);
	cout << "有" << count_m << "个员工" << endl;
	for (int index = 0; plan_it != m.end() && index < count_m; plan_it++, index++) {
		cout << "姓名： " << plan_it->second.name << " 工资: " << plan_it->second.salary << endl;
	}
}

void showMapByTask(multimap<int, Employee>& m) {
//#define planningDep 0
//#define developDep 1
//#define artDep 2
	if (!m.empty()) {
		cout << "planning department" << endl;
		department(m, planningDep);

		cout << "developing department" << endl;
		department(m, developDep);

		cout << "art department" << endl;
		department(m, artDep);
	}
	else {
		cout << "this vector is empty" << endl;
	}
}