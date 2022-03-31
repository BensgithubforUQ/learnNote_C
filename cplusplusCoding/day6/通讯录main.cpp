#include <iostream>
#include <string>
#include "myHead.h"
#include <vector>
using namespace std;

//对象如下
//struct address {
//	string addrName;
//	int addrAge;
//	string addrGender;
//	vector<long long> addrNumber;
//	string addrAddress;
//	bool addrStarContacts;
//};

int main() {
	struct person addr;
	addr.addrName = "王冰明";
	addr.addrAge = 26;
	addr.addrGender = "男";
	addr.addrNumber = { 
		13034470589 
	};
	addr.addrAddress = "湖北省黄冈市浠水县",
	addr.addrStarContacts = true;
	struct address abs;
	abs.people.push_back(addr);
	//初始化一个嵌套的结构体，address包含person，并且用一个person对象初始化address中的vector对象。

	while (true) {
		struct person addrNew;
		int flag = 0;
		cout << "按任意键刷新界面，进入通讯录系统" << endl;
		//cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		menu();
		switch (getchar())
		{
		case '1':
			flag = addAddress(&abs,&addrNew);
			if (flag == 1) cout << "成功添加" << endl;
			else cout << "中止添加" << endl;
			break;//添加联系人

		case '2':
			cout << "请输入联系人姓名:" << endl;
			flag = searchAddress(&abs);
			break;//查找联系人
		case '3':
			flag = changeAddress(&abs);
			break;//修改联系人
		case '4':
			delAddress(&abs);
			break;//删除联系人
		case '5':
			delAddressList(&abs);
			break;//删除通讯录

		case '6':printAddressList(abs);//printAddress(addr); 
			break;//打印通讯录

		case '0':
			exitAddressList();
			break;//退出通讯录
		}
		std::system("pause");
		std::system("cls");

	}
	return 0;
}