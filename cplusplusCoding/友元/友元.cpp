#include <iostream>
#include <string>
using namespace std;

class Mate;
class Building;

class Mate {
public:
	void visit();
	Building* building;
	void visitFriend();
	Mate();
private:
};

class Building {//建筑物类
	friend void mate(Building* building);//全局函数是building的友元，可以访问building的私有成员
	friend class Mate;
	friend void Mate::visitFriend();
public:
	Building();
	Building(string s, string b) :m_settingRoom(s), m_bedRoom(b) {

	}
public:
	string m_settingRoom; //客厅
private:
	string m_bedRoom;//卧室
};

Building::Building() {//因为下面的类mate里面用堆区指针整了个对象指针，没有定义真实的类
	//因此如果这里不用无参的构造函数整一个初始化的话，那访问属性就会报错，因为不存在。
	m_settingRoom = "初始化客厅";
	m_bedRoom = "初始化卧室";
}
/*友元，特殊的函数或者类在类外访问到类内的private私有成员*/
//1.全局函数做友元
void mate(Building* building) {
	cout << " 全局函数mate访问public权限的：" << building->m_settingRoom << endl;

	cout << " 友元全局函数mate访问private权限的：" << building->m_bedRoom << endl;
}
//2.类做友元

void Mate::visit() {
	cout << "类Mate正在通过友元访问类Building的私有属性m_bedRoom: " <<building->m_bedRoom<< endl;
}
Mate::Mate() {
	//创建一个建筑物对象
	 building = new Building;
}
//3.成员函数做友元
void Mate::visitFriend() {
	cout << "类Mate中的成员函数正在通过友元访问类Building的私有属性m_bedRoom: " << building->m_bedRoom << endl;
}


int main() {
	Building b_global_friend_test("客厅", "卧室");
	mate(&b_global_friend_test);
	Mate m_class_friend_test;
	m_class_friend_test.visit();
	m_class_friend_test.visitFriend();
	return 0;
}