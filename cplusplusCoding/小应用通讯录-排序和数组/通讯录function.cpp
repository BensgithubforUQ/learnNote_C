#include "myHead.h"

//struct address {
//	string name;
//	int age;
//	string gender;
//	vector<int> number;
//	string address;
//	bool starContacts;
//};

//struct address {
//	vector<struct person> people;
//	const int max = 10;
//};

//增
void menu() {
	cout << "**********" << "1.添加联系人" << "**********" << endl;
	cout << "**********" << "2.查找联系人" << "**********" << endl;
	cout << "**********" << "3.修改联系人" << "**********" << endl;
	cout << "**********" << "4.删除联系人" << "**********" << endl;
	cout << "**********" << "5.删除通讯录" << "**********" << endl;
	cout << "**********" << "6.打印通讯录" << "**********" << endl;
	cout << "**********" << "0.退出通讯录" << "**********" << endl;
	cout << "按对应数字键继续" << endl;
}
int addAddress(struct address* ab,struct person *a) {
	cout << "是否继续添加联系人，否则输入y，其他继续" << endl;
	getchar();
	if (getchar() != 'y') {
		cout << "请输入姓名" << endl;
		string name;
		cin >> name;
		auto beg = ab->people.begin(), end = ab->people.end();
		int flag = 0;//用于标记是否是合并为同一用户，是就改为1.
		while (beg != end) {
			if (name == beg->addrName) {
				cout << "检测到同名用户，是否直接添加用户其他的号码？是，请输入y" << endl;
				getchar();
				if (getchar() == 'y') {
					cout << "请输入号码：" << endl;
					int newNumber = 0;
					cin >> newNumber;
					beg->addrNumber.push_back(newNumber);
					flag = 1;
				}
				else {
					cout << "取消并入同一个联系人，开始创建新的联系人：" <<name<< endl;
					a->addrName = name;
				}
			}
			beg++;
		}	
		if (flag == 0) {
			a->addrName = name;
			cout << "请输入性别" << endl;
			cin >> a->addrGender;
			cout << "请输入年龄" << endl;
			cin >> a->addrAge;
			cout << "请输入地址" << endl;
			cin >> a->addrAddress;
			cout << "请输入电话号码" << endl;
			int num = 0;
			cin >> num;
			a->addrNumber.push_back(num);
			cout << "请选择是否是星级联系人，如果是，请输入y" << endl;
			getchar();
			if (getchar() == 'y') {
				a->addrStarContacts = true;
			}
			else {
				a->addrStarContacts = false;
			}
			ab->people.push_back(*a);
		}
		return 1;
	}
	else {
		cout << "取消增加联系人信息" << endl;
		return 0;
	}
}
//删
int delAddress(struct address *ab) {
	auto beg = ab->people.begin(), end = ab->people.end();
	cout << "请输入姓名" << endl;
	string name;
	cin >> name;
	int flag = 0;//用于标记是否是合并为同一用户，是就改为1.
	while (beg != end) {
		if (name == beg->addrName) {
			cout << "检测到同名用户，是否直接删除？按y停止，其他继续" << endl;
			int size = (ab->people.size());
			getchar();
			
			if (getchar() != 'y') {
				ab->people.erase(beg);
				cout << "删除成功" << endl;
				break;
			}
			else {
				cout << "取消本次删除" << name << endl;
			}
		}
		beg++;
	}
	return 1;
}
//查
int searchAddress(struct address *a) {
	auto beg = a->people.begin(), end = a->people.end();
	string target;
	getchar();
	//getline(cin, target);
	cin >> target;
	while (beg != end) {
		int flag = 1, amount = 0;
		auto targetSize = target.size();
		for (int i = 0; i < targetSize; i++) {
			if (beg->addrName[i] != target[i]) {
				flag = 0;
				break;
			}
		}
		if (flag) {
			printAddress(*beg);
			amount++;
		}
		beg++;
		if (beg == end&& amount==0) {
			cout << "没有找到目标联系方式" << endl;
		}
		else {
			cout << "搜索完毕" << endl;
		}
	}
	return 1;
}
//改
int changeAddress(struct address * a) {
	cout << "请输入想要修改的联系人的名字" << endl;
	auto beg = a->people.begin(), end = a->people.end();
	string target;
	getchar();
	//getline(cin, target);
	cin >> target;
	while (beg != end) {
		int flag = 1, amount = 0;
		auto targetSize = target.size();
		for (int i = 0; i < targetSize; i++) {
			if (beg->addrName[i] != target[i]) {
				flag = 0;
				break;
			}
		}
		if (flag) {
			printAddress(*beg);
			getchar();
			cout << "确认是否修改此联系人信息,按y取消，其他键继续" << endl;
			char approval;
			cin >> approval;
			if (approval != 'y') {
				cout << "请输入姓名" << endl;
				cin >> beg->addrName;
				cout << "请输入性别" << endl;
				cin >> beg->addrGender;
				cout << "请输入年龄" << endl;
				cin >> beg->addrAge;
				cout << "请输入地址" << endl;
				cin >> beg->addrAddress;

				vector<long long> newNum;

				cout << "请输入电话号码" << endl;
				int num = 0;
				cin >> num;
				newNum.push_back(num);
				beg->addrNumber = newNum;
				cout << "请选择是否是星级联系人，如果是，请输入y" << endl;
				getchar();
				if (getchar() == 'y') {
					beg->addrStarContacts = true;
				}
				else {
					beg->addrStarContacts = false;
				}
			}
			else {
				cout << "取消修改此联系人信息" << endl;
			}
			amount++;
		}
		beg++;
		if (beg == end && amount == 0) {
			cout << "没有找到目标联系方式" << endl;
		}
		else {
			cout << "搜索完毕" << endl;
		}
	}
	return 1;
}
//印
void printAddress(struct person a) {
	cout << "姓名：" << a.addrName << endl;	
	cout << "年龄：" << a.addrAge << endl;
	cout << "性别：" << a.addrGender << endl;
	cout << "地址：" << a.addrAddress << endl;
	for (auto addv = a.addrNumber.begin(); addv != a.addrNumber.end(); addv++) {
		cout << "电话号码: " << (long long) * addv << endl;
	}
	if (a.addrStarContacts) {
		cout << "星级联系人 " << endl;
	}
	else {
		cout << "普通联系人 " << endl;
	}
}
//打印全部
void printAddressList(struct address a) {
	if (a.people.size()!=0) {
		auto beg = a.people.begin(),end = a.people.end();
		while (beg != end) {
			printAddress(*beg);
			beg++;
		}
	}
	else {
		cout << "通讯录是空的。" << endl;
	}
}
//全删
int delAddressList(struct address *a) {
	//int size = a->people.size();
	//while (size) {
	//	a->people.pop_back();
	//	size--;
	//}
	vector<struct person> peoNull;
	a->people = peoNull;
	cout << "通讯录已经清空" << endl;
	return 1;
}
//退
void exitAddressList() {
	cout << "真的要退出吗？继续请输入y，其他退出" << endl;
	getchar();
	if (getchar() != 'y') {
		exit(0);
	}
	else {
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
	}
}