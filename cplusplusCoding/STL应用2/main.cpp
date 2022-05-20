#include "Employee.h"
#include "functions.h"

int main() {
	vector <Employee> e_v;
	multimap<int, Employee>e_m;
	addElement(e_v);
	//showTaskGroup(e_v);
	assignTask(e_v, e_m);
	//showTaskGroup(e_m);
	showMapByTask(e_m);
	return 0;
}