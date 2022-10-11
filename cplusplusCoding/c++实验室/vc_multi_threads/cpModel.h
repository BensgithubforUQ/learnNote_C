#pragma once
#include "customer.h"
#include "person.h"
#include "producer.h"
#include "product.h"
#include <thread>
#include <mutex>
#include <windows.h>
#include <vector>
#include <stack>
#include <time.h>
#include <thread>
#include "ioProduct.h"


//enum PRODUCT_TYPE
//{
//	m_hamburger = 1, m_lamian = 2, m_cookie = 3
//};
//
//enum PERSON_TYPE
//{
//	m_customer = 0, m_hamburgerMaker = 1
//};


/*产品数组*/
std::vector<abstractProduct*> vecProduct; //

/*互斥锁*/
std::mutex mtxPrduct;

//std::unique_lock<std::mutex> unique_mtxPrduct(mtxPrduct);

/*条件变量*/
std::condition_variable condi_full;
std::condition_variable condi_empty;

/*记录制作产品的数量*/
static int intProductCount = 0;
const int MAX_PRODUCTAMOUNT = 100;

/*生产者*/ 
bool produce(Person * productMaker)
{
	while (1)
	{
		if (intProductCount >= MAX_PRODUCTAMOUNT)
		{
			std::cout << "（材料耗尽捏）已经制作了100份" << std::endl;
			break;
		}
		std::unique_lock<std::mutex> uni_mtxPrduct(mtxPrduct);

		if (vecProduct.size() >= 30)
		{
			condi_full.wait(uni_mtxPrduct);
			return false;
		}
		
		PERSON_TYPE perType = productMaker->personType;

		/*多种商品的创建*/
		switch (perType)
		{
		case m_hamburgerMaker:
			//make hamburger;
			for (int i = productMaker->get_int_handleCount() ; i > 0 && vecProduct.size() <= 30
				&& intProductCount < MAX_PRODUCTAMOUNT; i--)
			{
				vecProduct.push_back(new Hamburger("hamburger", 2.00, i));
				++intProductCount;
				std::cout << "thread ： " << std::this_thread::get_id() << " producer make a hamburger";
				std::cout<<" size : " << intProductCount << std::endl;

				saveProductInfo(*productMaker, *vecProduct.back());
			}
			break;
		default:
			break;
		}
		Sleep(500);
		uni_mtxPrduct.unlock();
		condi_empty.notify_all();
		Sleep(300);
	}
	
	return true;
}

/*消费者*/
void consum(Person* customer)
{
	while (1)
	{

		std::unique_lock<std::mutex> uni_mtxPrduct(mtxPrduct);

		if (vecProduct.empty())
		{
			if (intProductCount >= MAX_PRODUCTAMOUNT)
			{
				std::cout << "吃完了捏" << std::endl;
				break;
			}
			else
			{
				condi_empty.wait(uni_mtxPrduct);
			}
		}
		
		for (int i = 0; i < customer->get_int_handleCount() && !vecProduct.empty(); i++)
		{
			std::cout << "thread " << std::this_thread::get_id() << " customer eat a hamburger, left "
				<< vecProduct.size() - 1 <<" remain." <<std::endl;
			//vecProduct.back()->showAll();
			vecProduct.pop_back();
		}

		Sleep(400);
		uni_mtxPrduct.unlock();
		condi_full.notify_all();
		Sleep(200);
	}
}
