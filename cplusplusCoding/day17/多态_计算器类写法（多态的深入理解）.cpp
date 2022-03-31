#include <iostream>
#include <string>
using namespace std;
//计算器，非多态
class Calculator {//两个操作数的运算
public:
	int m_1;
	int m_2;
	int getResult(char oper) {//使用非多态的写法的话，如果需要扩展新的功能，就需要修改源码
		//而在真实的开发中，提倡开闭原则：对扩展进行开发，对修改进行关闭。
		switch(oper) {
			case '+':
				return m_2 +m_1;
				break;
			case '-':
				return m_2 - m_1;
				break;
			case '*':
				return m_2 * m_1;
				break;
			deafult:
				break;
		}
		return 0;
	}
};

void test_Calculator_normal() {//测试非多态的计算器类的计算器函数。
	Calculator c;
	c.m_1 = 2;
	c.m_2 = 3;
	cout << "+ :" << c.getResult('+') << endl;
	cout << "- :" << c.getResult('-') << endl;
	cout << "* :" << c.getResult('*') << endl;
}
//利用多态实现计算器
//先实现一个计算机的抽象类，基类。
class abstractCalculator {//为了利用多态，需要有父类
public:
	int m_1;
	int m_2;
	virtual int getResult() {//为了利用多态，需要提供一个虚函数，供子函数去重写
		return 0;
	};
};

//加法计算器类，继承父类
class AddCalculator : public abstractCalculator {
public:
	int getResult() {//为了利用多态，在子类中重写父类的虚函数
		return m_1 + m_2;
	}
};
//减法法计算器类，继承父类
class MinusCalculator : public abstractCalculator {
public:
	int getResult() {//为了利用多态，在子类中重写父类的虚函数
		return m_1 - m_2;
	}
};
//乘法计算器类，继承父类
class MultiplyCalculator : public abstractCalculator {
public:
	int getResult() {//为了利用多态，在子类中重写父类的虚函数
		return m_1 * m_2;
	}
};
//除法法计算器类，继承父类
class DivideCalculator : public abstractCalculator {
public:
	int getResult() {//为了利用多态，在子类中重写父类的虚函数
		if (m_2 != 0) return m_1 / m_2;
		else {
			cerr << "error m_2 = 0" << endl; 
			return 0;
		}
	}
};

class SurplusCalculator: public abstractCalculator {
public:
	int getResult() {//为了利用多态，在子类中重写父类的虚函数
		return m_1 % m_2;
	}
};

//由此看到多态的优势
/*
1.组织结构清晰
2.可读性强
3.对于前期和后期的扩展和维护性高
因此在开发之前，需要多考虑是否能用多态来实现，这样就可以把开发变得更加简单和清晰*/
void test_Calculator_polymorphism() {//测试多态的计算器类的计算器函数。
	abstractCalculator *abc0 = new AddCalculator;//发生多态,在堆区创造一个父类的指针
	abc0->m_1 = 3;
	abc0->m_2 = 2;
	cout << "+ :" << abc0->getResult() << endl;
	delete abc0;
	abstractCalculator* abc1 = new MinusCalculator;//发生多态,在堆区创造一个父类的指针
	abc1->m_1 = 3;
	abc1->m_2 = 2;
	cout << "- :" << abc1->getResult() << endl;
	delete abc1;
	abstractCalculator* abc2 = new MultiplyCalculator;//发生多态,在堆区创造一个父类的指针
	abc2->m_1 = 3;
	abc2->m_2 = 2;
	cout << "* :" << abc2->getResult() << endl;
	delete abc2;
	abstractCalculator* abc3 = new DivideCalculator;//发生多态,在堆区创造一个父类的指针
	abc3->m_1 = 3;
	abc3->m_2 = 2;
	cout << "/ :" << abc3->getResult() << endl;
	delete abc3;
	abstractCalculator* abc4 = new SurplusCalculator;//发生多态,在堆区创造一个父类的指针
	abc4->m_1 = 3;
	abc4->m_2 = 2;
	cout << "% :" << abc4->getResult() << endl;
	delete abc4;
}

//int main() {
//	test_Calculator_normal();
//	test_Calculator_polymorphism();
//	return 0;
//}