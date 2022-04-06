#include "workerManager.h"
//#include "worker.h"
#include "employee.h"
#include "boss.h"
#include "manager.h"
int main() {
	//创建workerManager类对象
	WorkerManager wm;
	/*AbstractWorker* w = NULL;
	w = new Employee("张三", 1, 1);
	w->showPersonalInfo();*/

	while (1) {
		wm.show_Menu();
		cout << "请输入你的选择：" << endl;
		int number;
		cin >> number;
		switch (number) {
		case 0://退出
			wm.exit_Menu();
			break;
		case 1://添加职工
			wm.addEmployee();
			break;
		case 2://显示职工
			wm.show_WorkerInfo();
			break;
		case 3://删除职工
			wm.delete_Worker();
			break;
		case 4://修改职工
			break;
		case 5://查找职工
			wm.search_Worker();
			break;
		case 6://排序职工
			break;
		case 7://清空数据
			break; 
		defualt:
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}