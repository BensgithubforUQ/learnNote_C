#include <iostream>
#include <string>
#include <vector>
using namespace std;

//int main() {
//	char a[] = "abcde"; //字符串
//	char b[6] = { 'a','b','c','d','e' }; //字符型数组,同时是字符串
//	char c[5] = { 'a','b','c','d','e' };
//	//strlen c语言的库函数
//	cout << strlen(a ) << " " << strlen(b) <<" "<<strlen(c)<< endl;
//	//sizeof c++的运算符
//	cout << sizeof(a) << " " << sizeof(b) << " " <<sizeof(c) << endl;
//	printf("%s, %d\n", b,&b);
//	printf("%s, %d\n", c,&c);
//
//	//memcpy
//	int i1[5]{1,2,3,4,5};
//	int i2[]{5,5,5,5};
//	memcpy(i1, i2, 20);
//	for (int i = 0; i < 5; i++) cout << i1[i] << " ";
//
//	//strcpy
//	char i3[]{'a','b','c','d','e','g','h','i'};
//	const char *i4 = "abcdefg";
//	strcpy_s(i3, i4); //不会检测目标缓冲区大小，太小会报错，太大会直接覆盖
//	printf("%s\n", i3);
//	return 0;
//}