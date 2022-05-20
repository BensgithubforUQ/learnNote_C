#include "myHead.h"	
#include "circle.h"
/*
c++面向对象的三大特性：封装，继承，多态
c++认为万事万物都是对象，对象有其属性和行为

具有相同性质的对象，可以被抽象为 “类”，比如人类。

封装：
封装的意义是：
1.将属性和行为作为一个整体，来表现生活中的事物；
2.将属性和行为加以权限控制

封装的意义之一：《将属性和行为作为一个整体，来表现生活中的事物》
语法 class 类名{访问权限：属性}
封装的意义二：访问权限：
公共权限 public
保护权限 protected
私有权限 private
*/
//封装的意义1：
//设计一个圆类，求圆的周长
const double Pi = 3.14;
double Circle::calculatePerimeter() {//获取圆的周长
	return 2 * Pi * r_c;
}
void Circle::setPoint(Point c_p) {
	center = c_p;
}
void Circle::getPoint(int *x,int *y) {
	*x = center.getX();
	*y = center.getY();
}
