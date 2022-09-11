#include "abstractFactory.h"
#include <vector>
#include <string>
#include "testClass.h"
#include <fstream>
using namespace std;
vector<int> dp;
bool isPr(int n) {
	int size = dp.size();
	for (int i = 0; i < size; i++) {
		if (n % dp[i] == 0) return false;
		if (dp[1] > sqrt(n)) break;
	}
	return true;
}

void printPr(int n) {
	dp.push_back(2);
	dp.push_back(3);
	//5  7 -> 11  13
	for (int i = 5; i <=n; i += 6) {
		if (isPr(i)) dp.push_back(i);
		if (i + 2 <=n) {
			if (isPr(i + 2)) dp.push_back(i + 2);
		}
	}
	
	for (auto i : dp) cout << i << " ";
}

void findString(string s) {
	fstream file;
	file.open("car.txt", ios::in);
	string _str;
	if (file.is_open()) {
		cout << "open file successfully..." << endl;
		while (file >> _str) {
			cout << _str << endl;
			for (int i = 0; i < _str.size(); i++) {
				if (_str[i] == s[0]) {
					for (int j = i; j < s.size(); j++) {

					}
				}
			}
		}
	}
	file.close();
}

int main() {
	/*FatherFactory* a = nullptr;
	a = new SonFactory1;
	FatherProduct* p1 = a->product1();*/

	//prime
	//printPr(30);

	/*Test a;
	Test b(1, 2);
	Test c(b);
	c.changeTest(1, 1);
	Test d = c;
	a.printTest();
	b.printTest();
	c.printTest();
	d.printTest();*/
	return 0; 
}