#include "myHead.h"

void printArray(int* arr, int len) {
	cout << "输出int类型的数组：";
	for (int i = 0; i < len;i++) {
		cout << *(arr + i) << " ";
	}
	cout << endl;
}