#include<iostream>
#include"factory.hpp"
#include"abstractFactory.hpp"
using namespace std;

void test_factory() {
	//工厂模式
	Factory* fac = new ConcreteFactory();
	Product* pro = fac->CreateProduct();
	delete fac;
	delete pro;
	//经过测试，发现factory和product除了是用工厂类调用create产品类以外，没有关系，析构顺序不相关。
	//工厂模式的优势在于，构造工厂类，然后调用createXXX方法(该方法里面封装了new XXX的操作)，不用在意XXX的参数和名字
	//缺点在于，对于XXX和YYY产品，需要构造一个新的XXX工厂类或者新的YYY工厂类，然后要创建还要先new该工厂类这就是麻烦的点了。
	//关键：会造成类爆炸。
}

void test_abstract_factory() {
	//抽象工厂模式-factory模式实现new多种factory，然后factory具体类中实现多product类的对象的创建，在一个工厂里聚合多个产品
	AbstractFactory* ab_fac = nullptr;
	ab_fac = new ChineseFactory;
	AbstractApple *apple =  ab_fac->createApple();
	AbstractBanana* banana = ab_fac->createBanana();

	apple->showName();
	banana->showName();

	delete banana;
	delete apple;
	delete ab_fac;
	//优点，解决了类爆炸的问题。
	//缺点，解决类爆炸的方法很屮，在扩展产品族的时候，需要在工厂类的基类和子类里面添加方法。扩展难。
}

int main() {
	
	test_abstract_factory();
	
	return 0;
}