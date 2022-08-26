#ifndef SINGLETON_HPP
#define SINGLETON_HPP
#include<iostream>
#include<mutex>
using namespace std;
mutex my_mutex;
//线程不安全的-懒汉模式-改-线程安全版
class SingletonLazy {
public:
	static SingletonLazy* getInstance() {
		if (pSingleton == nullptr) { //双判，防止多线程不安全
			mutex_t.lock(); 
			if (pSingleton == nullptr) { //双判，防止多线程不安全
				pSingleton = new SingletonLazy();
				count++;
				cout << "懒汉模式，new了一个单例..." << endl;
			}
			else {
				cout << "双判第二判 false " << endl;
			}
			mutex_t.unlock();
		}
		else {
			cout << "双判第一判 false " << endl;
		}
		return pSingleton;
	}
	static bool getCount() {
		if (count == 1) return true;
		return false;
	}

	class innerCG {
	public:
		~innerCG(){
			delete SingletonLazy::pSingleton;
			pSingleton = nullptr;
			cout << "内部类自动释放,有 "<<SingletonLazy::count<<"个实例，同时delete pSingleton" << endl;
			count--;
		}
	};
	/*利用C++栈对象消亡是会自动回收的特点，来自动回收分配在堆上的单例对象
		可以通过四种方法：友元类、内部类 + 静态数据成员、atexit()函数、pthread_once() + atexit()来实现*/

private:
	static SingletonLazy* pSingleton;
	static mutex mutex_t;
	static innerCG gc;
	static int count;
	//将构造方法全部私有化
	SingletonLazy() {}; //私有化构造函数
	SingletonLazy(const SingletonLazy&) = delete;
	SingletonLazy& operator=(SingletonLazy&) = delete;
};
SingletonLazy* SingletonLazy::pSingleton = nullptr; //静态成员变量，类内定义，类外初始化。
mutex SingletonLazy::mutex_t;
SingletonLazy::innerCG SingletonLazy::gc;
int SingletonLazy::count = 0;


//线程安全的-饿汉模式
class SingletonHungry {
public:
	static SingletonHungry* getinstance() {
		if (pSingleton != nullptr) cout << "use getinstance..." << endl;
		else cout << "seems the object had been deleted..." << endl;
		return pSingleton;
	}

	static void freeSpace() {
		if (pSingleton != nullptr) {
			delete pSingleton; 
			pSingleton = nullptr;
			cout << "freeSpace..." << endl;
		}
		else {
			cout << "nothing to delete..." << endl;
		}
	}
private:
	static SingletonHungry* pSingleton;
	SingletonHungry() {}
};
SingletonHungry* SingletonHungry::pSingleton = new SingletonHungry; //是对象不能访问，并不是类不能访问
#endif // !SINGLETON_HPP
