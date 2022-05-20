#pragma once
#include <iostream>
#include  <string>
#include <vector>
#include <time.h>
using namespace std;

//这里有个坑，两个类不能互相需要对方的属性，不然就会报错。如果会出现这种情况，最好用类外的全局函数实现
//而不是像本次一样非得用成员函数实现
//而这里就发现实际上一个类，是可以包含另外一个类的。
//class Point {//点类，第五个实例，用于测试圆和点的关系
//public:
//	void setPointCoordinate(double x, double y); //设置点的属性
//	void relationship(double x, double y, double r_c);
//	double getX();
//	double getY();
//private:
//	double x_p_coordinate;
//	double y_p_coordinate;
//};
//
//class Circle {
//	//Perimeter = 2*PI*r;
//	//访问权限
//	//公共权限
//public:
//	//类中的属性和行为，都叫做类的成员
//	//属性
//	double r_c;//半径
//	//行为	
//	double calculatePerimeter();//获取圆的周长
//	void setPoint(Point c_p);
//	void getPoint(int *x,int *y);
//	//double getX() {
//	//	return x_c_coordinate;
//	//}
//	//double getY() {
//	//	return y_c_coordinate;
//	//}
//	//void setXY(double x, double y) {
//	//	x_c_coordinate = x;
//	//	y_c_coordinate = y;
//	//}
//private:
//	Point center;
//};
//
