#pragma once
#include "product.h"
#include "customer.h"
#include "producer.h"
#include <fstream>
#include <cassert>
#include <thread>
#include <sstream> 

bool saveProductInfo(Person& _producer, abstractProduct& _product)
{
	std::fstream ofs;
	ofs.open("product.txt", std::ios::app);
	
	assert(ofs);

	std::string ofs_productInfo;
	
	std::stringstream ss;
	auto thread_id = std::this_thread::get_id();
	ss << thread_id;



	ofs_productInfo += get_strProductName(_product)
		+ " " + std::to_string(get_doubleProductPrice(_product))
		+ " " + std::to_string(gett_longProductId(_product))
		+ " " + "produced by"
		+ " " + std::to_string(_producer.personType)
		+ " " + ss.str() + "\n";

	ofs.write(ofs_productInfo.c_str(), ofs_productInfo.size());

	return true;
}