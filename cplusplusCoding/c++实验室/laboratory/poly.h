#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Poly {
public:
	Poly() {};
	Poly(int x, char y,char *z) :a(x),b(y),c(z) {};
	virtual ~Poly() {};
	virtual void print_po() {};
private:
	int a = 1;
	char b = 'a';
	char* c = &b;
	int a1 = 2;
	int a2 = 3;
	int a3 = 4;
	int a4 = 5;
};