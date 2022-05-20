#include<iostream>
#include<string>
#include "myHead.h"
using namespace std;

//函数定义
//定义一个加法函数add
int add(int num1, int num2) {
	int sum = num1 + num2;
	return sum;
}

void swap(int num1,int num2) {
	int temp = 0;
	temp = num1;
	num1 = num2;
	num2 = temp;
}

int main() {
	int num1 = 0, num2 = num1;
	cin >> num1 >> num2;
	cout << add(num1, num2) << endl;
	cout << num1 << " " << num2 << endl;
	swapL(num1, num2);
	//形参改变不会改变实参。
	cout << num1 << " " << num2 << endl;
	return 0;
}