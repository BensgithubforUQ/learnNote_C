#include <iostream>
#include <string>
using namespace std;

//案例描述，电脑组成部件为 cpu（功能计算），显卡（功能显示），内存条（功能储存）
//将每个零件封装成抽象基类，并且提供不同的厂商生产不同的零件，比如intel和Lenovo
//创建电脑类，提供让电脑类工作的函数，并且调用零件工作的接口
//测试组装三台不同的电脑来工作。
class Cpu {//intel ,AMD
public:
	//计算
	virtual void calculate_cpu() = 0;
};

class GraphicsCard {//NVIDIA,AMD
public:
	//显示
	virtual void send_graphic_info() = 0;
};

class RAM {//kingston ,samsung
public:
	//储存
	virtual void memory() = 0;
};

class intelCpu : public Cpu {
public:
	void calculate_cpu() {
		cout << "intel cpu begins to calculate" << endl;
	}
};

class AMDCpu : public Cpu {
public:
	void calculate_cpu() {
		cout << "AMD cpu begins to calculate" << endl;
	}
};

class NVIDIAVideoCard : public GraphicsCard {
public:
	void send_graphic_info() {
		cout << "NVIDIA video card begins to work" << endl;
	}
};	

class AMDVideoCard : public GraphicsCard {
public:
	void send_graphic_info() {
		cout << "AMD video card begins to work" << endl;
	}
};

class KingstonRAM : public RAM {
public:
	void memory() {
		cout << "Kingston RAM Stores info" << endl;
	}
};

class SamsungRAM : public RAM {
public:
	void memory() {
		cout << "Samsung RAM Stores info" << endl;
	}
};

class Computer {
public:
	Computer(Cpu* c, GraphicsCard* g, RAM* m) {//用传入的对象指针来构造电脑类
		cpu = c;
		GC = g;
		mem = m;
	}
	void work() {//调用接口，让零件工作起来
		cpu->calculate_cpu();
		GC->send_graphic_info();
		mem->memory();
	}

	~Computer() {
		if (cpu != NULL) {
			delete cpu;
			cpu = NULL;
		}
		if (GC != NULL) {
			delete cpu;
			GC = NULL;
		}
		if (mem != NULL) {
			delete cpu;
			mem = NULL;
		}
		cout << "析构computer类" << endl;
	}
private:
	Cpu* cpu;//电脑类的成员属性是一些抽象类的指针
	GraphicsCard* GC;
	RAM* mem;
};

void test_assemble_a_computer() {
	Computer *c1 = new Computer(new intelCpu,new NVIDIAVideoCard,new KingstonRAM);
	Computer *c2 = new Computer(new AMDCpu, new AMDVideoCard, new KingstonRAM);
	Computer *c3 = new Computer(new intelCpu, new AMDVideoCard, new SamsungRAM);
	cout << "the first computer works" << endl;
	c1->work();
	delete c1;
	cout << endl;
	cout << "the second computer works" << endl;
	c2->work();
	delete c2;
	cout << endl;
	cout << "the third computer works" << endl;
	c3->work();
	cout << endl;
	delete c3;
}

int main() {
	test_assemble_a_computer();
	return 0;
}