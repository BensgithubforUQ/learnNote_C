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

void test_string3() {
	//查找
	string s1 = "abcdefghde";
	//需要查找s1中是否有子串“de"
	//int find(const string & str, int pos = 0)const;
	//pos是起始位置，因为默认为0，所以可以不输入
	string target_s1 = "de";
	int target_postion = s1.find(target_s1);
	cout << "de的位置是：" << target_postion << endl;//存在该值的时候
	target_s1 = "ed";
	target_postion = s1.find(target_s1);
	cout << "de的位置是：" << target_postion << endl;//不存在该值的时候，输出-1
	//因此这个可以用作判断
	target_postion = s1.rfind("de");
	cout << "de的位置是（rfind）：" << target_postion << endl;
	//rfind是从右往左查
}

void test_string4() {
	//替换 replace
	string s1 = "abcdefgh";
	s1.replace(1, 3, "1111");
	cout << "替换1-3号字符为1111：" << s1 << endl;//从1号位置开始，到，3号位置，替换为1111，注意是直接替换
	//无所谓替换成几个字符。
}

void test_string5() {
	//字符存取的操作
	string s1 = "abcdefghi";
	cout << "s1: " << s1 << endl;
	cout << "size of s1 is :" << sizeof(s1[0]) / sizeof(s1)<<endl;
	cout << "size of s1 is :" << s1.size() << endl;//封装了这个方法，和上面那个一样
	cout << "output the 5th element with []:" << s1[4] <<endl;
	cout << "output the 5th element with at:" << s1.at(4) << endl;
	//字符修改
	s1[4] = '1';
	cout << "output the 5th element with []:" << s1[4] << endl;
	s1.at(4) = '2';
	cout << "output the 5th element with at:" << s1.at(4) << endl;

}

void test_string6() {
	//字符串的插入和删除
	//insert
	string s1 = "abcd";//原字符串
	s1.insert(1, "111");
	cout << "在第1个位置，插入“111”：" << s1 << endl;
	string s2 = "efg";
	s1.insert(1, s2);
	cout << "在第1个位置，插入字符串说：" << s1 << endl;
	//删除erase
	s1.erase(1, 3);//从第n个位置开始，删除m个，记住起始坐标从0开始
	cout << "从第1个位置开始，删除3个字符" << s1 << endl;
}

void test_string7() {
	//子串
	//substring（int pos，int npos）从第pos位置开始，截出一个npos长度的子串，返回
	string s1 = "abcdef";
	string s2 = s1.substr(1, 3);
	cout << "从第1个位置开始，截一个长度为3的字符串" << s2 << endl;
}

void test_string8() {
	//实际操作，取邮箱@前的用户名
	string s_email = "zhangsan@qq.com";
	int pos = s_email.rfind('@');
	string account_name = s_email.substr(0, pos);
	cout << "用户名为：" << account_name <<endl;
}