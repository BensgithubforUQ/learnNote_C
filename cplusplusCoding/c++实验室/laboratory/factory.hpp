#ifndef FACTORY_HPP
#define FACTORY_HPP
#include <iostream>
using namespace std;

//定义创建对象的接口，封装对象的创建
//但是把具体化（创建哪种子类）的工作延迟到子类中。

class Product { //product的基类，抽象类
public:
	virtual ~Product() = 0 { cout << "~Product deconstruct..." << endl; }; //基类，纯虚函数,实现也没用的
protected:
	Product(){ cout << "Product construct..." << endl; }
private:
	
};

class ConcreteProduct :public Product { //public继承
public:
	~ConcreteProduct() { cout << "~concreteProduct deconstruct..."<<endl; }
	ConcreteProduct() { cout << "concreteProduct construct..." << endl; }
protected:
private:
};

class Factory {
public:
	virtual ~Factory() = 0 { cout << "~factory deconstruction..." << endl; };
	virtual Product* CreateProduct() = 0 {};
protected:
	Factory() { cout << "factory construction..." << endl; }
private:
};

class ConcreteFactory : public Factory {
public:
	~ConcreteFactory(){ cout << "~concreteFactory deconstruct..." << endl; }
	ConcreteFactory() { cout << "ConcreteFactory construction..." << endl; }
	Product* CreateProduct() { return new ConcreteProduct(); }
};

#endif // 

