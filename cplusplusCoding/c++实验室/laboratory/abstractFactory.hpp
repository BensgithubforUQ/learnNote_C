#ifndef ABSTRACTFACTORY_HPP
#define ABSTRACTFACTORY_HPP
#include <iostream>
using namespace std;

//苹果产品
class AbstractApple {
public:
	virtual ~AbstractApple() = 0 { cout << "~苹果基类析构..." << endl; };
	virtual void showName() = 0;
	AbstractApple() { cout << "苹果基类构造..." << endl; }
private:
};

class ChineseApple :public AbstractApple { //子类
public:
	virtual ~ChineseApple() { cout << "~中国苹果析构..." << endl; };
	void showName() { cout << "中国苹果!!!" << endl; }
	ChineseApple() { cout << "中国苹果构造..." << endl; }
private:
};

class AmericanApple :public AbstractApple { //子类
public:
	virtual ~AmericanApple() { cout << "~美国苹果析构..." << endl; };
	void showName() { cout << "美国苹果!!!" << endl; }
	AmericanApple() { cout << "美国苹果构造..." << endl; }
private:
};

//香蕉产品
class AbstractBanana {
public:
	virtual ~AbstractBanana() = 0 { cout << "~香蕉基类析构..." << endl; };
	virtual void showName() = 0;
	AbstractBanana() { cout << "香蕉基类构造..." << endl; }
private:
};

class ChineseBanana :public AbstractBanana { //子类
public:
	virtual ~ChineseBanana() { cout << "~中国香蕉析构..." << endl; };
	void showName() { cout << "中国香蕉？？？" << endl; }
	ChineseBanana() { cout << "中国香蕉构造..." << endl; }
private:
};

class AmericanBanana :public AbstractBanana { //子类
public:
	virtual ~AmericanBanana() { cout << "~美国香蕉析构..." << endl; };
	void showName() { cout << "美国香蕉？？？" << endl; }
	AmericanBanana() { cout << "美国香蕉构造..." << endl; }
private:
};

//抽象工厂 针对产品族
class AbstractFactory {
public:
	virtual AbstractApple* createApple() = 0;
	virtual AbstractBanana* createBanana() = 0;
protected:
private:
};

class ChineseFactory:public AbstractFactory {
public:
	virtual AbstractApple* createApple() {
		return new ChineseApple;
	}
	virtual AbstractBanana* createBanana() {
		return new ChineseBanana;
	}
private:
};

class AmericanFactory :public AbstractFactory {
public:
	virtual AbstractApple* createApple() {
		return new AmericanApple;
	}
	virtual AbstractBanana* createBanana() {
		return new AmericanBanana;
	}
private:
};
#endif // !ABSTRACTFACTORY_HPP

