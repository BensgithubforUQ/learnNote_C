#include <iostream>
#include <fstream>
#include <string>
#include "test.h"
using namespace std;


const  string p2 = "abc";
char s2[]  = "abc";
const string* ps1 = &p2;

template<typename T>
void func(const T& param) {
	const  string p1 = "abc"; 
	const char *s1 = "abc";
	cout << "p1:" << (int)&p1 << " s1:" << (int)&s1 << endl;
}

int test_114 = 114514;

int main() {
	func("abc");
	cout << "p2:" << (int)&p2 << " s2:" << (int)&s2 << endl;
	static int s4 = 2;
	int s5 = 3;
	cout << "s4: " << (int)&s4 << "  s5: " << (int)&s5 <<endl;
	string s3 = "abcedgiiiiiiiiiiiiiiiiiiii";
	string s6 = "abcedg";
	cout << "s3:" << (int)&s3 << " s3[17]:" << (int)&(s3[17]) << endl;
	cout << "s6:" << (int)&s6 << " s3[2]:" << (int)&(s6[2]) << endl;

	
	const string* ps = &s6;
	cout << "ps: " << (int)&ps <<  " ps1 " << (int)&ps1 <<endl;


	static int* p_i = new int(0);
	cout << "*pi " << (int)&(*p_i) << " p_i " << (int)&p_i << endl;
	const int x = s4;
	s4 = 5;
	cout << x << " " <<s4<< endl;

	printTest(10);
	return 0;
}