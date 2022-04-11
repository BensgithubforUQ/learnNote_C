#pragma once
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

//string是c++风格的字符串，而本质上string是一个类
//char * 是一个指针
//string是类，类内部封装了char* ，管理这个字符串，是一个char*型的容器

//string类里面封装了find，copy，delete，replace，insert等成员函数
//同时string不用担心复制越界和取值越界的问题，管理了char*所分配的内存

void test_string0() {//测试构造函数
	/*现在我们知道了，string实际上是一个封装了char*的类，那它的构造函数如下*/
	string s1;//默认构造，不初始化
	s1 = "bye";//赋值操作
	const char* str = "hello world";//创建一个char*类型的字符串
	string s2(str);//因为string是封装了char*的类，因此这个就是他的有参构造的使用方式，把c_string转化为string
	string s3(s2);//拷贝构造
	string s4(10, 'h');//一种重载的特殊的有参构造，用n个类似的字符初始化
	cout << s1 << " " << s2 << " " << s3 << " " << s4 << endl;
}

void test_string1() {
	/*sting容器有很多种赋值操作
	* string& operator=(const char* s); //将char* 类型的字符串	赋值 给当前字符串
	string& operator=(const string& s); //将string类型的对象，赋值给 当前字符串
	string& operator=(char c); // 将字符c，赋值 给当前字符串
	string& assign(const char* s); // 将字符串s赋值给当前字符串
	string& assign(const char* s,int n); //将字符串s的前n个字符，赋值给当前字符串
	string& assign(const string & s);//将字符串s赋值给当前字符串
	string& assign(int n,,const char c);//将n个字符c赋值给字符串
	*/
	string str1,str2;//默认初始化
	str1 = "hello";
	str2 = "world";
	cout << str1 << " ";
	str1 =  str2 ;
	cout << str1 << " ";
	char c1 = 'a';
	str1 = c1;
	cout << str1 << endl;
	str1.assign(str2);
	cout << str1 << " ";
	str1.assign("hello world", 3);
	cout << str1 << " ";
	str1.assign("you are welcome");
	cout << str1 << " ";
	str1.assign(5, c1);
	cout << str1 << endl;
}

void test_string2() {
	/*string的拼接*/
	/*主要有重载的+=和append来实现拼接，可以拼接char*，string和char*/
	string s1 = "hello s1";
	string s2 = "world s2";
	char c1 = 'c';
	const char* c2 = "c2 is a char*";
	s1 += s2;
	cout << s1 << endl;
	s1 += ':';
	cout << s1 << endl;
	s1 += c1;
	cout << s1 << endl;
	s1 += c2;
	cout << s1 << endl;
	//append
	cout << "append" << endl;
	string s3 = "i";
	s3.append(s1);
	cout << s3 << endl;
	s3.append(s1, 5);
	cout << s3 << endl;
	s3.append("love you",4);
	cout << s3 << endl;
	//灵活的append
	string s4("never");
	s4.append("i have a dream that came true", 2, 25);
	cout << s4 << endl;
}