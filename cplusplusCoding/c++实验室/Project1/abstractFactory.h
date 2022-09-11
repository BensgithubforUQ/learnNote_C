#ifndef ABSTRACTFACTORY_H
#include <iostream>
using namespace std;
class FatherProduct {
public:
	 FatherProduct() {}
	 virtual ~FatherProduct() = 0 {};
};

class SonProduct1:public FatherProduct{
public:
	SonProduct1() {}
	virtual ~SonProduct1() {}
};

class SonProduct2 :public FatherProduct {
public:
	SonProduct2() {}
	virtual ~SonProduct2() {}
};

class FatherFactory {
public:
	//virtual ~FatherFactory() = 0;
	virtual FatherProduct* product1() = 0;
	virtual FatherProduct* product2() = 0;
};

class SonFactory1:public FatherFactory {
public:
	SonFactory1() {}
	//~SonFactory1() {}
	FatherProduct* product1() {
		cout << "new a factory1's product1" << endl;
		return new SonProduct1;
	}
	FatherProduct* product2() {
		cout << "new a factory2's product2" << endl;
		return new SonProduct2;
	}
};
#endif // !ABSTRACTFACTORY_H

