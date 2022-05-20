#include "stack_test.h"
#include "queue_test.h"
#include "list_test.h"
#include "Person.h"
#include <time.h>
#include <string>

/*list—自定义数据Person 排序规则：
按照年龄进行升序排列，如果年龄相同，按照身高进行降序排列*/

void p_array_show(Person* p, int size) {
	if (size) {
		for (int i = 0; i < size; i++) {
			p[i].showInfo();
		}
	}
	else {
		cout << "blank array" << endl;
	}
}

void p_array_show(list<Person> l) {//重载一个链表版本的
	if (!l.empty()) {
		for (list<Person>::iterator it = l.begin(); it != l.end(); it++) {
			//(*it).showInfo();
			it->showInfo();
		}
	}
	else {
		cout << "blank array" << endl;
	}
}

//利用回调函数写sort的排序规则
bool comparePerson(Person &p1, Person &p2) {//这段真尼玛精华，草。
	//按照年龄升序
	if (p2.getAge() == p1.getAge()) return p1.getheight() > p2.getheight();//高级排序的实现方法
	return p2.getAge() > p1.getAge();//单级排序
}


//int main() {
//	//stack_test0();
//	//queue_test0();
//	//list_test0();
//	srand((unsigned int)time(NULL));
//	int size = 20;
//	Person* p_array = new Person[size];
//	list<Person> p_list;
//	for (int i = 0; i < size; i++) {
//		char name_temp = (i + 65);
//		string name{ name_temp };
//		int age = rand() % 25 + 20;
//		float height = (rand() % 30 + 160) + (rand() / double(RAND_MAX));
//		Person p_temp(name, age, height);
//		p_array[i] = p_temp;//数组版本
//		p_list.push_back(p_temp);//list版本
//	}
//	//p_array_show(p_array, 5);
//	p_array_show(p_list);
//	//排序
//	cout << "//排序:" << endl;
//	p_list.sort(comparePerson);
//	p_array_show(p_list);
//	delete[] p_array;//释放堆区内存
//	p_array = NULL;
//	return 0;
//}