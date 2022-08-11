#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <mutex>
using namespace std;
//所谓的智能指针，就是一个类模板，可以创建任意类型的指针对象，当对象使用完之后，就调用析构函数去释放内存
class test {
public:
	test() { cout << "构造···" << endl; }
	~test() { cout << "析构···" << endl; }

	int getDebug() { return this->debug; }
private:
	int debug = 20;

};
//自定义一个智能指针
template <class T>
class smartptr {
private:
	T* ptr;//指针对象
public:
	smartptr(T* _ptr): ptr(_ptr) { //有参构造
		cout << "smartptr的构造" << endl;
	}

	smartptr(smartptr& pre_p) :ptr(pre_p.ptr) { //auto_ptr风格的拷贝构造
		pre_p.ptr = nullptr;
	}

	//unique_ptr风格的 拷贝构造
	//smartptr(smartptr& pre_p) = delete;

	~smartptr() {
		if (ptr != nullptr) {
			cout << "smartptr的析构" << endl;
			delete ptr;
			ptr = nullptr;
		}
	}

	T& operator*() {
		return *ptr;//重载*运算符
	}
	T& operator->() {
		return ptr;//重载->运算符
	}

	T& operator=(smartptr<T>& pre_p) { //auto_ptr风格的赋值重载函数
		if (ptr != pre_p.ptr) {
			ptr = pre_p.ptr;
			pre_p.ptr = nullptr;
		}
		return ptr;
	}

	//unique_ptr风格的赋值重载函数
	//T& operator=(smartptr<T>& pre_p) = delete;

	bool operator==(T* p) { //测试一下auto_ptr风格的智能指针的资源管理权转移。
		if (ptr == p) return true;
		else return false;
	}
};

//auto_ptr因为会失去对资源的管理权会导致程序崩溃，所以已经被弃用，而unique_ptr则直接不能拷贝或者赋值构造。

//share_ptr

//引入计数器来实现指针共享资源。

template<class T>
class sh_p {
private:
	T* ptr; //指针对象
	int* count;//计数
	mutex* mt;
public:
	sh_p(T* _ptr):ptr(_ptr) { //默认构造
		count = new int(1);
		mt = new mutex;
		cout << "share_ptr的默认构造" << endl;
	}
	
	void addCount() {
		mt->lock();
		(*count)++;
		mt->unlock();
	}

	sh_p(sh_p<T>& sh) :ptr(sh.ptr), count(sh.count), mt(sh.mt) { //拷贝构造
		cout << "share_ptr的拷贝构造" << endl;
		addCount();
	}

	void release() { //释放的情况，如果计数为空，就释放资源，否则就无视该操作。
		bool flag = false;
		mt->lock();
		cout << "count--，现在为" << *count << endl;
		if (--(*count) == 0) { //注意每次release都--了count;
			delete count;
			delete ptr;
			count = nullptr;
			ptr = nullptr;
			cout << "share_ptr的析构" << endl;
			flag = true;
		}
		mt->unlock();
		if (flag) {
			delete mt;
			mt = nullptr;
		}
	}

	sh_p<T>& operator=(const sh_p<T>& sh) {
		if (sh.ptr != ptr) {
			release(); //释放旧资源，虽然不一定释放的了，因为旧资源可能不止一个指针在引用。
			ptr = sh.ptr;
			count = sh.count;
			mt = sh.mt;
			addCount();
			cout << "share_ptr的赋值构造" << endl;
		}
		return *this;
	}

	~sh_p() {
		release();
	}

	int& use_count() {
		return *count;
	}

	T& operator*() {
		return *ptr;//重载*运算符
	}
	T& operator->() {
		return ptr;//重载->运算符
	}

};



//int main() {
//	smartptr<int> ptr1(new int(114514));
//	cout << *ptr1 << endl;
//	smartptr<int> ptr2(ptr1);
//	if (ptr1 == nullptr) cout << "ptr1已经失去对资源的管理权" << endl;
//
//	sh_p<int> ptr3(new int(110));
//	cout << *ptr3 << endl;
//	sh_p<int> ptr4(ptr3);
//	cout << ptr3.use_count() << endl;
//
//	//share_ptr好用，但是有缺陷，比如在双向链表中，如果pre和next是互相引用，那就会计数2，使用完之后都析构，也只能把计数-1
//	//这样就有内存泄漏。这里称为循环引用。、
//	//因此需要weak_ptr; weak指针是定义在结构体里面的，可以指向share_ptr,但是并不会addcount，就解决了在循环引用的问题。
//	return 0;
//}

//struct node { //循环引用范例 - 用weak解决
//	shared_ptr<node> pre; //weak_ptr<node> pre;
//	shared_ptr<node> nex; //weak_ptr<node> nex;
//};
//
//int main() {
//	shared_ptr<node> n1;
//	shared_ptr<node> n2;
//	n1->nex = n2;
//	n2->pre = n1;
//
//	shared_ptr<int> num1(new int(0));
//	return 0;
//}