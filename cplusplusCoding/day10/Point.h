#pragma once
#include "myHead.h"
//#include "Circle.h" 这里不能包含这个头文件，因为circle类的头文件那边需要这边的类
//如果包含circle的头文件，会在找源的时候就读取那边，但是那边又会读取这边，那边并没有获取到point
//因此这里如果类似梅比乌斯蛇的调用，就会报错，逻辑性有问题
//有点先有鸡还是先有蛋的意思、
using namespace std;

class Point {//点类，第五个实例，用于测试圆和点的关系
public:
	void setPointCoordinate(double x, double y); //设置点的属性
	void relationship(double x, double y, double r_c);
	double getX();
	double getY();
private:
	double x_p_coordinate;
	double y_p_coordinate;
};