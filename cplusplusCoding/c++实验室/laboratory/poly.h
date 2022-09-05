#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
static int testint = 10;
class Poly {
public:
	Poly() { cout << "父类的构造" << endl; };
	virtual ~Poly() { cout << "基类的析构" << endl; };
	virtual void print_po() {};
private:
};

class Poly_son:virtual public Poly {
public:
	Poly_son() {};
	Poly_son(int x) :a(x) { cout << "子类的构造" << endl; };
	virtual ~Poly_son() { cout << "子类的析构" << endl; };
	virtual void print_po() { cout << "子类的print" << endl; };
	virtual void print_po(int x) { cout << "子类的print:" << x<<endl; };
private:
	int a = 1;
};

class Poly_daughter :virtual public Poly {
public:
	Poly_daughter() {};
	Poly_daughter(char x) :b(x) { cout << "子类的构造" << endl; };
	virtual ~Poly_daughter() { cout << "子类的析构" << endl; };
	virtual void print_po() { cout << "子类的print" << endl; };
	virtual void print_po(int x) { cout << "子类的print:" << x << endl; };
private:
	char b = 1;
};

class Poly_grandson :public Poly_son, public Poly_daughter {
public:
	Poly_grandson()  { cout << "孙类的构造" << endl; };
	~Poly_grandson() { cout << "孙类的析构" << endl; };
	virtual void print_po() { cout << "孙类的print" << endl; };
	virtual void print_po(int x) { cout << "孙类的print:" << x << endl; };
private:
};