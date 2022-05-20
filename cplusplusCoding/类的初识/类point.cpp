#include "myHead.h"	
#include "point.h"
/*
* 实例5，判断点和圆的关系
* 需要一个point类型和一个circle类型
* 都含有坐标属性，圆还有半径属性，此处重复利用案例一中定义的类。
*/

	void Point::setPointCoordinate(double x, double y) {//设置点的属性
		x_p_coordinate = x;
		y_p_coordinate = y;
	}
	void Point::relationship(double x1,double y1,double r_c) {
		double x = x1;
		double y = y1;
		double distance = (x_p_coordinate - x) * (x_p_coordinate - x) + (y_p_coordinate - y) * (y_p_coordinate - y);
		double rSquare = r_c * r_c;
		cout << "x: " << x << " y:" << y << endl;
		cout << "x_p: " << x_p_coordinate << " y_p:" << y_p_coordinate << endl;
		cout << "distance: " << distance << " r^2: " << rSquare << endl;
		if (distance == rSquare) {
			cout << "点在圆上" << endl;
		}
		else if (distance > rSquare) {
			cout << "点在圆外" << endl;
		}
		else if (distance < rSquare) {
			cout << "点在圆内" << endl;
		}
	}
	double Point::getX() {
		return x_p_coordinate;
	}
	double Point::getY() {
		return y_p_coordinate;
	}

