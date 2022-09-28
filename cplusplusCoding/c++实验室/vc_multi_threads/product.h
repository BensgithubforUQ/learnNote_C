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
	virtual ~abstractProduct() = 0 
	{
		
	}

	std::string set_strProductName(std::string _name)
	{
		return _strProductName =  _name ;
	}

	double set_strProductPrice(double _price)
	{
		return _doubleProductPrice =  _price ;
	}

	std::string set_strProductId(std::string id)
	{
		return _strProductId = id ;
	}

	void showAll()
	{
		std::cout << _strProductName << " "
			<< _doubleProductPrice << " "
			<< _strProductId << " " << std::endl;
	}
protected:
private:
	std::string  _strProductName; // {}
	double  _doubleProductPrice; //[]
	std::string  _strProductId; //()
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
	virtual ~Hamburger()
	{

	}

	Hamburger()
	{
		set_strProductName("");
		set_strProductPrice(0.00);
		set_strProductId("h000000");
	}

	Hamburger(std::string _name, double _price, std::string _id)
	{
		set_strProductName(_name);
		set_strProductPrice(_price);
		set_strProductId(_id);
	}
private:

};