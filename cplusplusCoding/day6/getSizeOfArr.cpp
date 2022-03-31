#include "myHead.h"

int  getSizeOfArr(int *arr) {
	int len = sizeof(arr) / sizeof(*arr);
	return len;
}