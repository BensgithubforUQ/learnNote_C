#include "myHead.h"

void popArr(int* arr, int len) {
	bool flag = false;
	for (int i = len; i >1; i--) {
		flag = false;
		for (int j = 0; j < i-1; j++) {
			if (*(arr + j) > *(arr + j + 1)) {
				int temp = *(arr + j);
				*(arr + j) = *(arr + j + 1);
				*(arr + j + 1) = temp;
				flag = true;
			}
		}
		if (flag == false) {
			break;
		}
	}
}