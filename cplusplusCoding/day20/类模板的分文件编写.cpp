#include "virtual_son_template.hpp"
//因为类模板的成员函数在调用的时候才创建。
/*因此，如果分文件写的话，会导致在查询.h文件的时候，无法链接到该函数
所以会把类模板的声明和类模板的成员函数定义写在一个头文件里，并且文件后缀是hpp*/



void test_vitural_fatherToSon_classTemplate() {//测试用父类引用调用多态，当然，这里只实现了单一的子类对象。
	abstractFather<string, int, int>* aF =
		new son_template_father<string, int, int, string>("张三", 10, 30, "大墩子镇");
	aF->showInfo();
	delete aF;
}
void test_vitural_fatherToSon_classTemplate2() {//测试子类中的友元全局函数，打印son类的数据
	son_template_father<string, int, int, string> sF("李四", 10, 30, "小墩子镇");
	printThisClassInfo(sF);
}
//int main() {
//	test_vitural_fatherToSon_classTemplate();
//	cout << "*****************" << endl;
//	test_vitural_fatherToSon_classTemplate2();
//	system("pause");
//	return 0;
//}