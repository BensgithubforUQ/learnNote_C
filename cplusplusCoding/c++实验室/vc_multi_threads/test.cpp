#include "cpModel.h"

namespace ben{
	/*测试Person基本的构造函数等*/
	void test_person_construct() {
		Person defaultPrsn;
		Person valuePrsn(2);
		Person copyPrsn(valuePrsn);
		defaultPrsn = copyPrsn;

		std::cout << " Get total person amount: " << Person::getPersonAmount() << std::endl;
	}
	 
	/*测试customer类和person类的多态*/
	void test_customer_getConsumeCount() 
	{
		Person* testCstmr = new Customer(2,2);
		std::cout << testCstmr->getPersonAmount()<<std::endl;
		delete testCstmr;
	}

	/*测试产品类（hambuger）基本的构造函数等*/
	void test_product_makeHamburger() 
	{
		abstractProduct* hmbrgr = new Hamburger("chicken",21.00,"00000");
		hmbrgr->showAll();
	}

	/*测试基础的vc++的多线程操作*/
}

int main() {


	ben::test_person_construct();

	ben::test_customer_getConsumeCount();
	
	ben::test_product_makeHamburger();

	return 0;
}