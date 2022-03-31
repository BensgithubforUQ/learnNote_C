#pragma once
#include "myHead.h"
#include "Point.h"
using namespace std;

class Circle {
	//Perimeter = 2*PI*r;
	//访问权限
	//公共权限
public:
	//类中的属性和行为，都叫做类的成员
	//属性
	double r_c;//半径
	//行为	
	double calculatePerimeter();//获取圆的周长
	void setPoint(Point c_p);
	void getPoint(int* x, int* y);
	//double getX() {
	//	return x_c_coordinate;
	//}
	//double getY() {
	//	return y_c_coordinate;
	//}
	//void setXY(double x, double y) {
	//	x_c_coordinate = x;
	//	y_c_coordinate = y;
	//}
private:
	Point center;
};
