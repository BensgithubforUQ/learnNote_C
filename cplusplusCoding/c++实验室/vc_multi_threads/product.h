#pragma once
#include <iostream>
#include <string>
#include <algorithm>


/******************
* class : abstractProduct 产品类基类
* value :
private:
*	std::string  _strProductName; // 产品名
*	double  _doubleProductPrice; //产品价格
*	std::string  _strProductId; //产品id
******************/
class abstractProduct 
{
public:
	PRODUCT_TYPE pType;
public:
	virtual ~abstractProduct() = 0 
	{
		
	}

	std::string set_strProductName(std::string _name)
	{
		return _strProductName =  _name ;
	}

	double set_doubleProductPrice(double _price)
	{
		return _doubleProductPrice =  _price ;
	}

	long set_longProductId(long id)
	{
		return _longProductId = id ;
	}

	void showAll()
	{
		std::cout << _strProductName << " "
			<< _doubleProductPrice << " "
			<< _longProductId << " " << std::endl;
	}
protected:
private:
	std::string  _strProductName; // {}
	double  _doubleProductPrice; //[]
	long  _longProductId; //()
};

/******************
* class : Hamburger 具体产品类
* value :
private:
*	std::string  _strProductName; // 产品名（继承）
*	double  _doubleProductPrice; //产品价格（继承）
*	std::string  _strProductId; //产品id（继承）
******************/
class Hamburger : public abstractProduct
{
public:

public:
	virtual ~Hamburger()
	{

	}

	Hamburger(std::string _name, double _price, long _id)
	{
		set_strProductName(_name);
		set_doubleProductPrice(_price);
		set_longProductId(_id);
		pType = m_hamburger;
	}
private:

};

class Lamian : public abstractProduct
{
public:
	virtual ~Lamian()
	{

	}

	Lamian(std::string _name, double _price, long _id)
	{
		set_strProductName(_name);
		set_doubleProductPrice(_price);
		set_longProductId(_id);
		pType = m_lamian;
	}
private:

};

class Cookie : public abstractProduct
{
public:
	virtual ~Cookie()
	{

	}

	Cookie(std::string _name, double _price, long _id)
	{
		set_strProductName(_name);
		set_doubleProductPrice(_price);
		set_longProductId(_id);
		pType = m_cookie;
	}
private:

};