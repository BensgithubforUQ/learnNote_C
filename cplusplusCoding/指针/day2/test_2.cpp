#include <iostream>
#include <string.h>
#include "Sales_data.h"
using namespace std;
//
//int main() {
//	int val = 1;
//	int *p = &val;
//	//int* q = 2;这也是错的。
//	int* q = 0; //但是这是可以的。
//	//等同于：
//	//int* q = nullptr;
//	cout << p<<" "<<*p<<" "<<val<<endl;
//	*p = 2;
//	cout << p << " " << *p << " " << val << endl;
//	//该实验验证了一个事实，即p存着指向val的地址，p是val的指针。
//	//如果修改*p的值，等同于修改p指向的对象的值。
//	//而修改*p的值，不会改变p存储的值，即val的地址。
//	return 0;
//}

//int main() {
//	int i = 42;
//	int* p1 = &i;
//	*p1 = *p1 * *p1;
//	cout << *p1 << " " << p1 << " " << i;
//	return 0;
//}

//int main() {
//	int i = 10;
//	//double *dp = &i;
//	int* p = &i;
//	//int *p = i;
//	int *q = nullptr;
//	//q = i;
//	if (p) cout << "yes" << endl;
//	if (*p) cout << "no" << endl; //如果p存储的地址指向的对象的值为0，则这条读不出来、
//	return 0;
//}

//int main() {
//	int i = 42; //申明定义并且初始化i为一个int类型的变量，值为42
//	int* p; //定义一个指针p
//	int*& r = p; //r是p的引用。
//
//	//这里的*&r的意思是r是指针p的引用。从右边往左边读，因此*&r是引用，而*证明，r是引用其他的指针。
//	r = &i; //将i的地址赋值给引用r，即是赋值给指针p
//	*r = 0; //将引用r，即指针p的地址解指针，就得到了p的地址所指向的变量i，*r，*p，i在这时是同义词。
//	cout << i << " " << r << " " << *r << " " << p << " " << *p << endl;
//	//因此，i的值就被赋值为0，然后*r，和*p解指针得到的值，也是0.
//}

//int main() {
//	int i = 45;
//	int& r1 = i;
//	const int& r2 = i;
//	cout << i << " " << r1 << " " << r2<<endl;
//	r1 = 42;
//	//r2 = 41;
//	cout << i << " " << r1 << " " << r2;
//	return 0;
//}

//int main() {
//	int i = 42;
//	const int* p = nullptr;
//	p = &i;
//	//*p = 45;因为*p指向的是i，并且是指向常量的指针不可修改，因此不可通过该指针修改指向的对象的值。
//	cout << p << " " << *p;
//	return 0;
//}

//int main() {
//	//注意，指向常量的指针和常量指针并不一样。
//	int i = 3, h = i;
//	const int j = i, & r = i,*p0 = &i;
//	cout << j << " " << r <<" "<<*p0<< endl;
//	int* const p = &i;
//	int *p1 = &i;
//	p1 = &h;
//	const int* const p2 = &i;
//	const int& const r1 = 0;
//	cout << i << " " << p1 << " " << r1 << " " << p2 << endl;
//	*p = 4;
//	
//	int* q = nullptr;
//	//p = q;//这里就表现出来了，p本身是常量，是一个常量指针，因此不可以用右边的的空指针对他进行赋值。
//	p1 = q;//但是非常量指针就可以被赋值。改变存储的地址。
//	cout << i <<" " << p1 <<" " <<r1<<" "<<p2<< endl;
//	return 0;
//	//因此这里要注意的是，是const int *p还是 int *const p；
//	//int *const p的含义是p这个常量指针不可变，但是他指向的对象可变、
//	//const int *p是int *p这个指针指向的是常量，不可通过该指针修改指向的常量。
//}

//先看指向常量的部分，表达式左边如果是指向常量，那右边必须是可以转化为指向常量的，或者本身是常量。
//再看表达式左边是否是常量指针，如果是那他在初始化以外的情况下，不能出现在表达式左边。
//int main() {
//	int i = 0; //申明并且定义并且初始化，int类型的i的值为0；
//	int* const p1 = &i;//申明并且定义并且初始化，int类型的，常量指针p1.指向int类型的i；
//	const int ci = 42;//定义const int类型的ci；
//	const int* p2 = &ci;//定义指向常量的int类型的指针，p2。指向常量c1；底层const
//	const int* const p3 = p2;//定义指向常量的int类型的常量指针p3，用指向常量的int类型的指针p2初始化它。
//	//此时，左边的const是底层const，右边的const是顶层const。
//	//在拷贝的时候，顶层const无所谓，因为拷贝不会改变被拷贝对象的值。
//	//而必须考虑底层const，两边的对象必须有相同的底层资格。
//	const int& r = ci;//申明引用的const都是底层const
//
//	i = ci; // i是int类型的变量，ci是const int 类型的常量，常量可以转化为变量，所以合法、
//	p2 = p3;//p2是指向常量的int类型的指针，p3是指向常量的int类型的常量指针，底层const都是指向常量的资格一致。
//	//而右边的p3的常量指针在这次操作中不会被改变，因此合法。
//	//但是如果此时整这一出
//	//p3 = p2;//这就会出问题，因为虽然底层const资格一致，但是p3是常量指针，因此不能出现在表达式左边。
//	
//	//int* p = p3; //这样也会出问题，因为p3的底层资格里面有const，而int *p没有，因此非法。
//	p2 = p3;//同上，合法。
//	p2 = &i;//p2是指向常量的int类型的指针，而int*类型可以转化成const int*类型，因此合法。
//	//int& r = ci; // 因为c1是const int类型的常量，而普通的int& 不能绑定到常量上。
//	const int& r2 = i;
//	system("puase");
//	return 0;
//}

//constexpr int weekday = 5;
//#define weekend 2;
//int main() {
//	const int v2 = 0;
//	int v1 = v2;
//	int* p1 = &v1;
//	int& r1 = v1;
//	const int* p2 = &v2, *const p3 = p2,&r2 = v2;
//	r1 = v2;
//	//p1 = p2; //底层const资格不一样，不能赋值
//	p2 = p1; //底层const类型资格虽然不一样，但是int*可以转化const int *；
//	//p1 = p3; //同上
//	p2 = p3;
//	system("pause");
//	return 0;
//}

//int main() {
//	int i = 0, & r = i;
//	auto a = r; //int a = r;
//	//auto 会忽略顶层const但是会保留底层const
//	const int ci = i, & cr = ci;
//	auto b = ci; // int b = ci;
//	auto c = cr; // int c = ci;
//	auto d = &i; //int *d = &i;
//	auto e = &ci;//&ci，ci是整数常量，因此&ci是指向整数常量的指针，这个指向整数常量就是底层const。
//	//因此是const int* e = &ci;
//	const auto f = ci;//const int f = ci；如果需要强制保留顶层const，则需要自己加const。
//	auto& g = ci;//ci是整数常量，因此这个是const int &g = ci;
//	//auto& h = 42;这个是错的，是因为42是整数，而非顶层const的引用不可绑定字面值。
//	//int& g1 = 42; 参考这个。
//	const int& g2 = 42;
//	const auto& j = 42;
//
//	auto k = ci, & l = i;//k = ci,忽略顶层const，int k = i；int &l = i；都是正确的。
//	auto& m = ci, * p = &ci;//ci是顶层const的整数常量，因此是const int &m = ci,const int *p = &ci;引用整数常量的m和指向整数常量的指针p。
//	//auto& n = i, * p2 = &ci; 这里报错是因为，i是整形，因此auto是int，int &n = i，是n引用int i。int *p2 =&ci，不合法。
//	//因为&ci是指向整数常量的指针，是const int*，是底层const，而左边是int *，底层const不一样，不能初始化。
//	a = 42;//给int类型的变量a赋值42，合法。
//	b = 42;//同上
//	c = 42;//同上
//	//d = 42;//d是int * 类型的，不能直接给指针对象赋常量
//	//e是指向常量的指针
//	//e = 42;同理也是不能直接给指针赋常量
//	//g = 42;g是const，不可变。
//	int& n = i;
//	n = 42;
//	return 0;
//}

//int main() {
//	const int i = 42;
//	auto j = i; //切记，在不在前面主动加const的情况下，auto会忽略顶层const。因此这里是int j = i.j是int类型而不是const int。
//	const auto& k = i;
//	auto* p = &i;
//	const auto j2 = i, & k2 = i;
//	return 0;
//}

//int main() {
//	const int a = 3;
//	int b = 4;
//	decltype(a) a1 = a; //这里的a1 是 const int类型的
//	auto a2 = a;//a2是int 类型的，因为a的const是顶层const被auto忽略了。
//	decltype(b) b1 = b;//b1是int类型的
//	auto b2 = b;//b2是int类型的
//	//这个例子展示了同一应用情境下，decltype和auto的区别。
//}


//struct Sales_data {
//	string bookNo;
//	unsigned units_sold = 0;
//	double revenue = 0.0;
//};
Sales_data accum, trans, * salesptr;
int main() {
	Sales_data data1, data2, data3;
	double price = 0;
	cout << "please input book number,units_sold and price:" << endl;
	cin >> data1.bookNo >> data1.units_sold>> price;
	data1.revenue = data1.units_sold * price;
	cin >> data2.bookNo >> data2.units_sold >> price;
	data2.revenue = data2.units_sold * price;
	if (data1.bookNo == data2.bookNo) {
		auto totalCnt = data1.units_sold + data2.units_sold;
		auto totalRevenue = data1.revenue + data2.revenue;
		cout << data1.bookNo << " " << totalCnt << " " << totalRevenue << " ";
		if (totalCnt != 0) {
			cout << totalRevenue / totalCnt << endl;
		}
		else cout << " no sales" << endl;
		return 0;
	}
	else {
		cerr << "data must refer to the same ISBN" << endl;
		return -1;
	}
}