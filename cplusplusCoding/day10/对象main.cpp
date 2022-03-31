#include "myHead.h"
#include "circle.h"
#include "Fruit.h"
//#include "point.h"这个也可以不写，因为circle.h已经用了point.h



//实例2：学生类，要求有姓名和学号，并且可以打印，赋值。
class Student {
	//访问权限
	//公共权限
public:
	//类中的属性和行为，都叫做类的成员
	/*s属性，也叫作成员属性，和成员变量
	姓名 string
	学号 long long
	*/
	string name_s;
	long long id_s;
	//行为，也称作成员函数，或者成员方法。
	//打印
	void printrInfo_s() {
		cout << "姓名: " << name_s << " id: " << id_s << endl;
	}
	void set_name_s(string *name) {
		name_s = *name;
	}
	void set_id_s(long long *id) {
		id_s = *id;
	}
};
//封装的意义二：三种权限，公共权限public，保护权限protected，私有权限private
/*
* public，成员类内可以访问，类外也可以访问
* protected，成员类内可以访问，类外不可访问，子类可以访问
* private, 成员类内可以访问，类歪不可以访问，子类不可访问
* protected和private的区别在于，继承的时候，子类可以访问父类的保护权限，但是不可以访问父类的私有权限。
* 成员设置成私有主要由两点好处：
* 1.可以控制读写的权限，因为类外不能访问，因此只能用类的成员函数来访问。
* 2.对于“写”操作，可以检测数据的有效性。
*/
class Person {//实例3
	//公共权限
public:
	string p_Name;
	//保护权限
protected:
	string p_Car;
	//私有权限
private:
	int p_Password;
	//成员函数：行为
public:
	void func() {
		p_Name = "张三";
		p_Car = "拖拉机";
		p_Password = 45591901;
	}

	void printrInfo_p() {
		cout << "姓名: " << p_Name << " 车: " << p_Car<< " 密码: " << p_Password << endl;
	}
};
/*
* 在c++中struct默认的访问权限为public;
* 而class的默认访问权限是private。
*/



/*案例4
* 练习案例，设一个立方体类，求出立方体的体积和面积
并且分别利用全局函数和成员函数判断两个立方体是否相等
* 访问权限，公共权限里面留一些接口，用于设置和获取立方体的信息，而私有属性里面设置立方体的属性。
*/
class Cubic {
	//访问权限
public:
	void setAttribute(double l, double w, double h) {//设置立方体的属性
		if (l > 0 && w > 0 && h > 0) {
			length = l;
			weight = w;
			height = h;
		}
		else {
			cerr << "长宽高的属性不符合标准，请输入大于0的长宽高" << endl;
		}
	}

	double getAttributeLWH(int a) {//获取长宽高
		switch(a) {
		case 1:
			return length;
			break;
		case 2:
			return weight;
			break;
		case 3:
			return height;
			break;
		default:
			cout << "长： " << length << "宽： " << weight << "高： " << height << endl;
			return 0;
			break;
		}
		cout << "长： " << length << "宽： " << weight << "高： " << height << endl;
	}

	void getVolume() {//获取体积
		cout << "体积： " << height*weight*length << endl;
	}

	void getSurfaceArea() {//获取面积
		cout << "体积： " << 2* height * weight + 2 * length * weight + 2 * height *  length << endl;
	}

	void isCubicSame_classfunc(Cubic c) {
		if (c.getAttributeLWH(1) == length && c.getAttributeLWH(2) == weight && c.getAttributeLWH(3) == height) {
			cout << "相同（成员函数判断结果）" << endl;
		}
		else {
			cout << "不同（成员函数判断结果）" << endl;
		}
	}

private:
	double length;
	double weight;
	double height;

};

//利用全局函数判断两个立方体是否相等
bool isCubicSame(Cubic c1, Cubic c2) {
	if (c1.getAttributeLWH(1) == c2.getAttributeLWH(1) && c1.getAttributeLWH(2) == c2.getAttributeLWH(2) && c1.getAttributeLWH(3) == c2.getAttributeLWH(3)) {
		cout << "相同（全局函数判断结果）" << endl;
		return true;
	}
	else {
		cout << "不同（全局函数判断结果）" << endl;
		return false;
	}
}



int main() {
	//通过圆类创建具体的对象，一个圆。
	Circle circle1; //通过一个类创建一个对象的过程，被称为“实例化”
	circle1.r_c = 10.0;
	cout << "圆类对象，circle1的周长为： " << circle1.calculatePerimeter() << endl;

	//实例化一个学生类的对象
	Student stu1;
	long long id = 45591901;
	string name = { "王冰明" };
	stu1.set_name_s(&name); //利用成员函数来给成员变量赋值
	stu1.set_id_s(&id);//利用成员函数来给成员变量赋值
	stu1.printrInfo_s();//利用成员函数来打印成员变量。
	
	//实例三：权限问题：
	//先实例化一个人物类
	Person zhangsan;
	zhangsan.p_Name = "张三的别名";
	//只有这一个成员变量可以在在类外访问。
	zhangsan.func();
	zhangsan.printrInfo_p();
	zhangsan.p_Name = "张三的别名";
	zhangsan.printrInfo_p();
	//但是可以通过调用类内的成员方法来变相的访问，打印。

	//实例4：立方体类，和立方体类的属性读取和判断立方体们是否相同。
	Cubic c_1, c_2, c_3;
	c_1.setAttribute(10.0, 10.0, 10.0);
	c_1.getAttributeLWH(4);
	c_1.getSurfaceArea();
	c_1.getVolume();
	//利用公有权限中的一系列接口（成员函数）获取一系列的c_1的私有属性。
	c_2.setAttribute(10.0, 10.0, 10.0);
	c_3.setAttribute(10.0, 10.0, 11.0);
	isCubicSame(c_1, c_2);
	isCubicSame(c_1, c_3);
	//利用全局函数判断立方体是否相同
	c_1.isCubicSame_classfunc(c_2);
	c_1.isCubicSame_classfunc(c_3);
	//利用类中的成员函数判断立方体是否相同


	//案例五，判断点和圆的关系
	//首先需要初始化两个对象
	Point p_1,p_2,p_3,c_p;
	Circle circle2;
	int x1 = 0, y1 = 0;
	p_1.setPointCoordinate(0.0, 1.0);
	p_2.setPointCoordinate(0.5, 0.5);
	p_3.setPointCoordinate(0, 0);
	c_p.setPointCoordinate(1, 1);
	circle2.setPoint(c_p);
	circle2.r_c = 1;
	circle2.getPoint(&x1, &y1);
	p_1.relationship(x1,y1,circle2.r_c);
	p_2.relationship(x1, y1, circle2.r_c);
	p_3.relationship(x1, y1, circle2.r_c);


	/*对象的初始化和清理*/
	//调用重载的构造函数
	//括号法
	Fruit apple;
	Fruit banana("yellow");
	Fruit banana1(banana);
	//注意事项：调用默认构造函数的时候，不要用小括号；
	banana.getColor();
	banana1.getColor();
	//显示法
	Fruit purple;
	Fruit watermelon = Fruit("green and black");
	//Fruit("green and black")这种对象单独拿出来叫匿名对象
	//当前行结束后，系统会马上自动回收这个匿名对象
	//而等号左值的watermelon就是他的名，下面直接演示匿名对象；
	Fruit("green and black");
	//可以发现马上就会自动调用析构函数，来清理这个匿名对象
	//注意事项2：不可用拷贝构造函数来初始化匿名对象
	//Fruit(watermelon);//会报错重定义
	Fruit watermelon1 = Fruit(watermelon);

	watermelon.getColor();
	watermelon1.getColor();
	//隐式转换法
	Fruit orange = watermelon;
	//会打印在析构和构造函数里面的信息（代码写了打印
	system("pause");
	return 0;
}