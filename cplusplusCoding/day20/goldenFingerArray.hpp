#pragma once
#include <iostream>
#include <string>
using namespace std;

/*需求
1.可以储存内置数据类型的对象和自定义数据类型的对象
2.将数组中的数据存放到堆区
3.构造函数中可以传入数组的容量
4.提供对应的拷贝构造函数以及operator=的重载防止浅拷贝
5.提供尾插法和尾删法来进行增加或者删除数组中的数据
6.可以通过下标访问
7.可以获取数组中当前元素的个数和数量*/

template <class T>
class goldenFingerArray {
public:
	void Push_Back(const T& value);//尾插法插入元素
	void Pop_Back();//尾删法
	goldenFingerArray(int capacity);//构造函数
	goldenFingerArray(const goldenFingerArray& arr);//为了防止浅拷贝的问题，需要重载一个拷贝构造函数
	~goldenFingerArray();//析构函数
	goldenFingerArray& operator=(const goldenFingerArray& arr);//为了防止浅拷贝的问题,需要重载一个赋值运算符。
	T& operator[](int index);//重载[]，实现a[i]功能，用下标访问
	int getCapacity();//获取数组的容量
	int getSize();
	void showArrInfo();//获取数组全部信息。
private://私有成员
	T* m_elementAddress; //数组中的元素，指针指向的是在堆区开辟的数组
	int m_Capacity; //数组的容量
	int m_size; //数组的大小
};

template <class T>
goldenFingerArray<T>::goldenFingerArray(int capacity) {//有参构造
	this->m_Capacity = capacity;
	this->m_size = 0;
	this->m_elementAddress = new T[this->m_Capacity];
	cout << "有参构造完成" << endl;
}

template <class T>
goldenFingerArray<T>::goldenFingerArray(const goldenFingerArray& arr) {
	this->m_Capacity = arr.m_Capacity;
	this->m_size = arr.m_size;
	this->m_elementAddress = new T[this->m_Capacity];//防止浅拷贝，需要自己重新开辟新的堆区空间
	//这是深拷贝

	//将arr中的数据都拷贝进来
	if (arr.m_Capacity != 0) {
		for (int i = 0; i < arr.m_size;i++) {
			this->m_elementAddress[i] = arr.m_elementAddress[i];
		}
		cout << "拷贝构造完成" << endl;
	}
}
template <class T>
goldenFingerArray<T> & goldenFingerArray<T>::operator=(const goldenFingerArray<T>& arr) {
	//因为=要实现一个连等的链式编程思想，因此每次=完了都要返回一个当前对象的地址
	//先判断原来堆区是否有数据，如果有，先要释放
	if (this->m_elementAddress != NULL) {
		delete[] this->m_elementAddress;
		this->m_elementAddress = NULL;
		this->m_size = 0;
		this->m_Capacity = 0;
	}
	//然后整个深拷贝
	this->m_Capacity = arr.m_Capacity;
	this->m_size = arr.m_size;
	this->m_elementAddress = new T[this->m_Capacity];//防止浅拷贝，需要自己重新开辟新的堆区空间
	//这是深拷贝

	//将arr中的数据都拷贝进来
	if (arr.m_Capacity != 0) {
		for (int i = 0; i < arr.m_size; i++) {
			this->m_elementAddress[i] = arr.m_elementAddress[i];
		}
		cout << "=重载中，拷贝构造完成" << endl;
	}

	//最后需要返回本对象
	return *this; //this是指针，*this返回的就是指针指向的对象
}


template <class T>
goldenFingerArray<T>::~goldenFingerArray() {
	if (this->m_Capacity != NULL) {
		delete[] this->m_elementAddress;
		this->m_Capacity = NULL;
		cout << "调用析构函数析构堆区数据" << endl;
	}
}

template <class T>
void goldenFingerArray<T>::Push_Back(const T& value) {
	if (this->m_Capacity == this->m_size) {
		cout << "数组容量已经满了，不可继续插入元素" << endl;
		return;
	}
	else {
		this->m_elementAddress[this->m_size] = value; //尾插
		this->m_size++;//长度++
	}
}

template <class T>
void goldenFingerArray<T>::Pop_Back() {
	if (this->m_size == 0) {
		cout << "数组容量空了，不可继续删除元素" << endl;
		return;
	}
	else {
		this->m_size--;//长度--
	}
}

template <class T>
T& goldenFingerArray<T>::operator[](int index) {//重载[]，实现a[i]功能，用下标访问
	return this->m_elementAddress[index];
	//返回的是&，可以作为左值。
}

template <class T>
int goldenFingerArray<T>::getCapacity() {
	return this->m_Capacity;
}

template <class T>
int goldenFingerArray<T>::getSize() {
	return this->m_size;
}


template <class T>
void goldenFingerArray<T>::showArrInfo() {
	cout << "数组容量： " << this->m_Capacity << endl;
	cout << "数组长度： " << this->m_size << endl;
	for (int i = 0; i < this->m_size;i++) {
		cout << this->m_elementAddress[i] << endl;
	}
}