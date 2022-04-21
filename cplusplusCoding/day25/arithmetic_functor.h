#pragma once
#include <functional>
#include <iostream>
using namespace std;

//算术仿函数
/*
template <class T> T plus<T> //加法仿函数
template <class T> T minus<T> //减法仿函数
template <class T> T multiples<T> //乘法仿函数
template <class T> T divides<T> //除法仿函数
template <class T> T modulus<T> //取模仿函数
template <class T> T negate<T> //取反仿函数
*/

void test_negate() {
	//negate 一元运算 取反
	negate<int>negate_int;
	int num = 10;
	num = negate_int(num);
	cout << "negate_int(num):" << num << endl;
}

void test_plus() {
	//add 二元运算 加
	plus<int>plus_int;
	int num1 = 1, num2 = 2;
	int sum = plus_int(num1, num2);
	cout << "plus_int(num1, num2):" << sum << endl;
}