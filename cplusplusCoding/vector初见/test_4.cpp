#include <iostream>
#include <string>
#include <vector>
using namespace std;

//int main() {
//	vector<vector<int>> ivec;
//	//vector<string> svec = ivec; 容器类型不一样，不能用ivec初始化svec；
//	vector<string> svec(10, "null");
//	vector<int> v1;
//	for (int i = 0; i < 100; i++) {
//		v1.push_back(i);
//	}
//	string str;
//	while (std::cin >> str) {
//		if (str == "exit") {
//			cout << "输入了回车键，退出str循环" << endl;
//			break;
//		}
//		svec.push_back(str);
//	}
//	std::cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
//	cout << "开始对v1容器进行输入，ctrl+z退出循环" << endl;
//	int num;
//	while (std::cin >> num) {
//
//		v1.push_back(num);
//	}
//	if (!v1.empty()) {
//		v1 = { 1,2,3,4,5 };
//		cout << "是否继续输入数字？y继续" << endl;
//		char c = getchar();
//		if (c == 'y'){
//			std::cin >> num;
//			v1.push_back( num);
//		}
//		cout << "v1 不为空,且包含" <<v1.size() <<"个元素" << endl;
//	}
//	return 0;
//}

//int main() {
//	int num;
//	vector<int> vn;
//	while (cin >> num) {
//		if (num == 114514) {
//			break;
//		}
//		vn.push_back(num);
//	}
//	int i = 0, j, k;
//	for (auto r : vn) {
//		if (i == 0) {
//			j = r;
//		}
//		else {
//			k = r;
//			cout << j + k << endl;
//			j = k;
//		}
//		i++;
//	}
//	for (decltype(vn.size()) x = 0; x != vn.size();x++) {
//		if (x >= vn.size() - x-1) {
//			break;
//		}
//		cout << vn[x] + vn[vn.size() - 1-x] << endl;
//	}
//	return 0;
//}

//迭代器
//int main() {
//	string str("haiyahaoqi1996wbm");
//	char c;
//	int i = 0;
//	while (cin >> c && i<5) {
//		i++;
//		str += c;
//	}
//	std::cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
//	
//	for (auto it = str.begin(); it != str.end() && !isspace(*it);it++) {
//		*it = toupper(*it);
//	}
//	cout << "the new string is " << str << endl;
//	return 0;
//}

//int main() {
//	string text{ "abcdefghijklmnopqrstuvwxyz" };
//	auto beg = text.begin(), end = text.end();
//	auto mid = beg + (end - beg) / 2;
//	char sought;
//	cin >> sought;
//	while (mid != end) {
//		if (sought < *mid) {
//			end = mid;
//		}
//		else if(sought > *mid) {
//			beg = mid+1;
//		}
//		else {
//			break;
//		}
//		mid = beg + (end - beg) / 2;
//	}
//	cout << "the location is " << mid - text.begin()+1;
//	return 0;
//}

//int main() {
//	vector<int> v1;
//	int num = 0,i = 0;
//	while (std::cin >> num&&i!=10) {
//		v1.push_back(num);
//		i++;
//	}
//	cout << "input completed" << endl;
//	auto beg = v1.begin(), end = v1.end()-1;
//	auto sum = beg;
//	while (end - beg > 0) {
//		*sum = *beg + *end;
//		beg+=1;
//		end-=1;
//		cout << *sum << endl;
//	}
//	return 0;
//}

//int main() {
//	vector<int> v1;
//	int num = 0, i = 0;
//	while (cin >> num && i != 10) {
//		i++;
//		v1.push_back(num);
//	}
//	auto beg = v1.begin(), end = v1.end();
//	
//	for (auto r = beg; r != end; r++) {
//		*r = *r * 2;
//		cout << *r << " ";
//	}
//	return 0;
//}

//int main() {
	//unsigned cnt = 42;
	//constexpr unsigned sz = 42;
	//int arr[10];
	//int* parr[sz];
	//string bad[sz];
	//const unsigned sz = 3;
	//int ial[5] = { 0,1,2 };
	//int a2[] = { 0,1,2 };
	//int a3[5] = { 0,1,2 };
	//string a4[3] = { "hi","bye" };

	//char c1[]{ 'c','+','+' };
	//char c2[]{ 'c','+','+','\0' };
	//char c3[] = "c++";
	//const char c4[7] = "daniel";
	//字符数组的特殊性，必须留一位给空字符，也可以是显式空字符"\n"
	//且数组不允许拷贝和用数组初始化其他数组
//	int ia[4 * 7 + 11];
//	int a[10] = {};
//	for (int i = 0; i < 10; i++) {
//		a[i] = i;
//	}
//	int i = 0;
//	int b[10] = {};
//	vector<int> varr;
//	for(auto p : a) {
//		b[i] = p;
//		varr.push_back(p);
//		cout << b[i] << " " << varr[i] << endl;
//		i++;
//	}
//	return 0;
//}

//int main() {
//	const int size = 5;
//	int a[size] = { 1,3,3,4,5 };
//	int b[size] = { 1,3,3,4,5 };
//	int c[size] = { 1,1,1,1,1 };
//	int p1 = a[0],p2 = a[1];
//	p1 += p2 - p1;
//	cout << p1 << endl;
//	int* p = a;
//	for (int i = 0; *(p+i) != *(a + 5); i++) {
//		*(p+i) = 0;
//	}
//	int* p3 = a;
//	for (p3; *p3 != *(a + 5); p3++) {
//		*p3 = 1;
//	}
//	int i = 0;
//	while (*(a+i)!=*(a+size)){
//		cout << *(a + i) <<endl;
//		i++;
//	}
//	int sizeA = sizeof(a)/sizeof(a[0]), sizeB = sizeof(b)/sizeof(b[0]), sizeC = sizeof(c)/sizeof(c[0]);
//	cout << sizeA << " " << sizeB << " " << sizeC << endl;
//	if (sizeA == sizeC) {
//		for (int i = 0; i != sizeA-1; i++) {
//			if (a[i] == c[i]) {
//				continue;
//			}
//			else {
//				cout <<i<<" " << a[i] << " " << c[i] << endl;
//				cout << "数组不一样" << endl;
//				return 1;
//			}
//		}
//		cout << "数组一样" << endl;
//	}
//	return 0;
//}

//int main() {
//	vector<int> va, vb;
//	int v = 0,i = 0,j=0;
//	while (cin >> v&&i<6) {
//		va.push_back(v);
//		i++;
//		if (i == 5) {
//			break;
//		}
//	}
//	
//	while (cin >> v && j < 6) {
//		vb.push_back(v);
//		j++;
//		if (j == 5) {
//			break;
//		}
//	}
//	cout << i << " " << j << endl;
//	auto bega = va.begin(), begb = vb.begin();
//	if (va.size() == vb.size()) {
//		cout << va.size() << " " << vb.size() <<endl;
//		int num = 1;
//		while (bega != va.end() && begb != vb.end()) {
//			if (*bega == *begb) {
//				cout << *bega << " " << *begb << endl;
//				++bega;
//				++begb;
//				num++;
//				continue;
//			}
//			else {
//				cout <<"第" << num << "个不一样" << endl;
//				return 1;
//			}
//		}
//	}
//	cout << "一样" << endl;
//	return 0;
//}

//冒泡排序
//int main() {
//	int a[9] = { 8,7,6,8,4,5,3,1,2 };
//	int size = sizeof(a) / sizeof(a[0]), i = size - 1, j = 0;
//	bool flag = false;
//	for (i = size - 1; i > 0; i--) {
//		flag = false;
//		for (j = 0; j < size-1; j++) {
//			if (a[j] > a[j + 1]) {
//				auto temp = a[j];
//				a[j] = a[j + 1];
//				a[j + 1] = temp;
//				flag = true;
//			}
//		}
//		if (flag == false) {
//			break;
//		}
//	}
//	for (auto value : a) {
//		cout << value << " ";
//	}
//	return 0;
//}

//使用数组初始化vector的时候，用地址来初始化。
//int main() {
//	int arr1[6] = {1,2,3,4,5,6},i=0;
//	vector<int> varr1(arr1,arr1+6);
//	vector<int> varr2(begin(arr1),end(arr1));
//	auto begVarr1 = varr1.begin(), begVarr2 = varr2.begin();
//	while (begVarr1 != varr1.end()) {
//		cout << *begVarr1 << " " << *begVarr2 << endl; //解地址来得到值
//		begVarr1++; //地址++，在容器内移位。
//		begVarr2++;
//	}
//	return 0;
//}

//int main() {
//	int a[5][5] = {
//		{10,20,30,40,50},
//		{11,21,31,41,51},
//		{12,22,32,42,52},
//		{13,23,33,43,53},
//		{14,24,34,44,54}
//	};
//	for (auto& i : a) {
//		for (auto j : i) {
//			cout << j << " ";
//		}
//		cout << endl;
//	}
//
//	//利用begin和end输出二维数组，注意指针操作。
//	int(*p)[5] = a; //p是一个指针，指向的维度为5的数组，数组类型是int
//	cout << *( * (p + 4)+4) << endl;
//	for (int(* p1)[5] = begin(a); p1 != end(a); p1++) {
//		for (int *p2 = begin(*p1); p2 != end(*p1); p2++) {
//			cout << *p2 <<" ";
//		}
//		cout << endl;
//	}
//	return 0;
//}

//int main() {
//	int grade[3][3] = {
//		{96,95,94},
//		{99,98,97},
//		{93,82,81}
//	};
//
//	for (auto &i : grade) {
//		int gradeSum = 0;
//		double gradeAverage = 0.0;
//		for (auto j : i) {
//			gradeSum += j;
//		}
//		cout << gradeSum << endl;
//		gradeAverage = (double)gradeSum / (sizeof(grade) / sizeof(*grade));
//		cout << gradeAverage<<endl;
//	}
//	return 0;
//}