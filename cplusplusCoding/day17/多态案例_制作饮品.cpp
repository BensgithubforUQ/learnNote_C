#include <iostream>
#include <string>
using namespace std;

class AbstractPrepareDrinks {
public:
	virtual void boilingWater() = 0;
	virtual void brewing() = 0;
	virtual void pouring() = 0;
	virtual void addingIngredients() = 0;
	virtual void allSteps() = 0;
};

class MakeTea :public AbstractPrepareDrinks {
public:
	void boilingWater() {
		cout << "boiling water for tea" << endl;
	}
	void brewing() {
		cout << "brewing tea" << endl;
	}
	void pouring() {
		cout << "pouring tea into cup" << endl;
	}
	void addingIngredients() {
		cout << "adding other ingredients into tea" << endl;
	}
	void allSteps() {
		boilingWater();
		brewing();
		pouring();
		addingIngredients();
	}
};

class MakeCoffee :public AbstractPrepareDrinks {
public:
	void boilingWater() {
		cout << "boiling water for Coffee" << endl;
	}
	void brewing() {
		cout << "brewing Coffee" << endl;
	}
	void pouring() {
		cout << "pouring Coffee into cup" << endl;
	}
	void addingIngredients() {
		cout << "adding other ingredients into Coffee" << endl;
	}
	void allSteps() {
		boilingWater();
		brewing();
		pouring();
		addingIngredients();
	}
};

void prepare(AbstractPrepareDrinks* a) {//穿的是指针
	a->allSteps();
	delete a;//这里已经释放了堆区的内存，外面就不需要再释放了。
}
//int main() {
//	AbstractPrepareDrinks* m_t = new MakeTea;
//	AbstractPrepareDrinks* m_c = new MakeCoffee;
//	prepare(m_t);
//	prepare(m_c);
//	
//	return 0;
//}