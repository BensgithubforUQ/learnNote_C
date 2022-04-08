#include <iostream>
using namespace std;

//函数模板
//普通函数调用可以发生隐式类型转换（比如可以把char型转换成int型来进行计算）。
// 函数模板	 用自动类型推导，不可发生隐式类型转换（因为没法替换成一致的类型，这里有二义性）
// 函数模板  用显示指定类型，可以发生隐式类型转换。（确定了转换的类型，就能计算，没有歧义）
//两个整型数交换函数


void swapInt(int& a, int& b) {
	int temp;
	temp = a;
	a = b;
	b = temp;
}
//两个浮点型数交换函数
void swapDouble(double& a, double& b) {
	double temp;
	temp = a;
	a = b;
	b = temp;
}

//上面两个function非常类似，逻辑一直，只是参数类型不一样
//这里可以用模板来操作

template<class T>//声明一个模板，告诉编译器，后面紧跟的T不报错，T是一个通用的数据类型
void mySwap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}
//这就是一个函数模板，函数模板+紧跟着的定义的一个函数中使用。
template<class T>
void SortArray(T arr[], int len) {
	if (len > 1) {
		for (int i = 0; i < len; i++) {
			//cout << arr[i] << endl;

			for (int j = i + 1; j < len; j++) {
				//cout << arr[i] <<" "<<arr[j] << endl;

				if (arr[i] < arr[j]) {
					mySwap(arr[i], arr[j]);
 				}
			}
		}
	}
	else {
		cout << "数据不足" << endl;
	}
}
template<class T>
void array_print(T arr[],int len) {
	for (int i = 0; i < len;i++) {
		cout << arr[i] << " ";
	}
}
/*
普通函数和函数模板的调用规则
1.如果函数模板和普通函数都可以调用，优先调用普通函数
2.可以通过空模板参数列表，强制调用函数模板
3.函数模板也可以重载
4.如果函数模板可以产生更好的匹配，则优先调用函数模板*/
void myPrint(int a, int b) {
	cout << "普通函数 a: " << a << " b: " << b << endl;
}

template<class T>
void myPrint(T a, T b) {
	cout << "函数模板 a: " << a << " b: " << b << endl;
}
template<class T>
void myPrint(T a, T b, T c) {
	cout << "函数模板,重载的模板 a: " << a << " b: " << b << " c: " << c << endl;
}

//int main() {
//	/*有两种方法使用函数模板*/
//	//1.自动类型推导，必须要推到出一致的数据类型才能用
//	int a = 10, b = 20;
//	mySwap(a, b);
//	cout << a << " " << b << endl;
//
//	/*普通函数和函数模板调用测试*/
//	myPrint(a, b);//调用普通函数，符合第一调用规则,就算普通函数只有声明，也调用普通函数，然后报错
//	//第二规则，通过空模板参数列表，可以强制调用函数模板
//	myPrint<>(a, b);//空模板参数列表
//	//函数模板的重载
//	myPrint(a, b,100);
//	//如果函数模板可以产生更好的匹配，则优先调用函数模板
//	myPrint('A', 'B');//其实形参为int的普通函数也可以成功调用，但是需要发生隐式类型转换
//	//因此在这种情况下，函数模板是更加优秀的匹配，就优先调用函数模板。
//	
//
//	//2.显示指定类型
//	mySwap<int>(a, b);//指定为int，必须指定了才能用
//	cout << a << " " << b << endl;
//	int arr[3] = { 3,1,2 };
//	int len = sizeof(arr) / sizeof(arr[0]);
//	SortArray(arr,len);
//	array_print(arr,len);
//
//	cout << endl;
//
//	char arr_s[] = "abcdefghijklmnopqrstuvwxyz";//不能用string哦,string是字符串，不是数组。是char类型的数组。
//	int len_s = sizeof(arr_s) / sizeof(arr_s[0]);
//	SortArray(arr_s, len_s);
//	array_print(arr_s, len_s);
//	system("pause");
//	return 0;
//}