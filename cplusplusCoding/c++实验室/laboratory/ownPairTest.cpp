#include "myOwnPair.hpp"

/*********************
Function:     testConstructAnd
Description:  测试自定义数据类型的构造，赋值，析构，和重载<<
Calls:        <<重载，=重载
Called By:    main
*********************/
void testConstructAnd()
{
	/*一个自定义类型数据（类似pair）的vector，测试无参构造*/
	std::vector<myOwnPair<char, int>> vecOwnPair(10, myOwnPair<char, int>());

	/*测试赋值，测试有参构造和拷贝*/
	for (int i = 0; i < vecOwnPair.size(); ++i)
	{
		vecOwnPair[i] = myOwnPair<char, int>('a' + i, i);
		std::cout << vecOwnPair[i] << " " << myOwnPair<char, int>::getOwnPairAmount() << std::endl;
	}

	/*测试resize，和析构*/
	vecOwnPair.resize(1);
	std::cout << myOwnPair<char, int>::getOwnPairAmount() << std::endl;
}

/*********************
Function:     testCmp
Description:  测试比较符<
Calls:        <重载
Called By:    main
*********************/
void testCmp()
{
	myOwnPair<char, int> cmpLeftPair('1', 1);
	myOwnPair<char, int> cmpRightPair('0', 2);

	/*测试 < 比较符*/
	if (cmpLeftPair < cmpRightPair)
	{
		std::cout << "yes,left is smaller." << std::endl;
	}
	else
	{
		std::cout << "No,left is bigger." << std::endl;
	}
}


int main() {
	testConstructAnd();
	testCmp();

	return 0;
}