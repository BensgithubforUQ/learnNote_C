#pragma once
#include "customer.h"
#include "person.h"
#include "producer.h"
#include "product.h"
#include <thread>
#include <mutex>
#include <windows.h>
#include <vector>

extern std::vector<abstractProduct*> vecProduct; //

class Locker
{
public:

private:
	std::mutex _mutex;
};

extern std::condition_variable condiPrdct;
