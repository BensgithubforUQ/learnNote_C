//#include "virtual_son_template.h"
//#include "virtual_father.cpp"
//
//template<class T1, class T2, class T3, class T4>
//void son_template_father<T1,T2,T3,T4>::showInfo() {
//	cout << this->name << endl;
//	cout << this->age << endl;
//	cout << this->id << endl;
//	cout << *(this->address) << endl;
//}
//
//template<class T1, class T2, class T3, class T4>
//son_template_father<T1, T2, T3, T4>::son_template_father(T1 n, T2 a, T3 i, T4 add) {
//	this->name = n;
//	this->age = a;
//	this->address = new T4(add);
//	this->id = i;
//	cout << typeid(T1).name() << endl;
//	cout << typeid(T2).name() << endl;
//	cout << typeid(T3).name() << endl;
//	cout << typeid(T4).name() << endl;
//}
//
//template<class T1, class T2, class T3, class T4>
//son_template_father<T1, T2, T3, T4>::~son_template_father() {
//	if (this->address != NULL) {
//		delete this->address;
//		this->address = NULL;
//		cout << "addressµÄÐéÎö¹¹" << endl;
//	}
//	
//}