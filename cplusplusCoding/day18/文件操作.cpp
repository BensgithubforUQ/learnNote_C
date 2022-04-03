#include <iostream>
#include <string>
#include <fstream>//文件读写必须写fstream
using namespace std;

void output_file() {//向流对象输入文件内容
	//创建流对象
	ofstream ofs;
	//指定打开的方式
	ofs.open("test.txt", ios::out);//第一个参数是路径，第二个参数是打开方式
	//写内容
	ofs << "姓名：王" << endl;
	ofs << "性别：男" << endl;
	ofs << "年龄：18" << endl;
	//打开了文件需关闭文件
	ofs.close();
}

int input_file() {//从流对象读取文件
	//创建流对象
	ifstream ifs;
	//打开文件
	ifs.open("test.txt", ios::in);
	if (!ifs.is_open()) {//如果成功打开文件，ifs.is_open会是bool类型的true
		cout << "文件打开失败，当前目录没有找到该文件" << endl;
		return 1;
	}

	//四种读取方法
	//1.while循环+字符数组的方法读取
	char buf1[1024] = {};
	while (ifs >> buf1) {
		cout << buf1 << endl;
	}
	ifs.close();
	//2.字符数组+ifs成员函数getline（）
	ifs.open("test.txt", ios::in);
	if (!ifs.is_open()) {//如果成功打开文件，ifs.is_open会是bool类型的true
		cout << "文件打开失败，当前目录没有找到该文件" << endl;
		return 1;
	}
	char buf2[1024] = {};
	while (ifs.getline(buf2, sizeof(buf2) / sizeof(buf2[0]))) {
		cout << buf2 << endl;
	}
	ifs.close();
	//3.string
	ifs.open("test.txt", ios::in);
	if (!ifs.is_open()) {//如果成功打开文件，ifs.is_open会是bool类型的true
		cout << "文件打开失败，当前目录没有找到该文件" << endl;
		return 1;
	}
	string buf3;
	while (getline(ifs,buf3)) {//一行行读取
		cout << buf3 << endl;
	}
	ifs.close();
	//get的方式
	ifs.open("test.txt", ios::in);
	if (!ifs.is_open()) {//如果成功打开文件，ifs.is_open会是bool类型的true
		cout << "文件打开失败，当前目录没有找到该文件" << endl;
		return 1;
	}
	char buf4;
	while ((buf4 = ifs.get()) != EOF) {//不推荐用第四种，一个个字符读，效率低
		//EOF,end of file,==eof就读到了文件尾部
		cout << buf4;
	}
	ifs.close();
	return 0;
}

class person {
public:
	char p_name[1024] = {};
		int p_age;
};

void output_file_binary() {
	//创建流对象
	ofstream ofs;
	ofs.open("person.txt", ios::out | ios::binary);
	//写文件
	person p = { "张三",18 };
	ofs.write((const char *)&p,sizeof(person));
}

int input_file_binary() {
	//创建流对象
	ifstream ifs;
	ifs.open("person.txt", ios::in | ios::binary);
	//写文件
	if (!ifs.is_open()) {//如果成功打开文件，ifs.is_open会是bool类型的true
		cout << "文件打开失败，当前目录没有找到该文件" << endl;
		return 1;
	}
	person p;
	ifs.read((char*)&p, sizeof(person)); //这个操作要记住了。read接口
	cout << p.p_name << endl;
	cout << p.p_age << endl;
	ifs.close();
}
int main() {
	
	//output_file();
	//input_file();
	output_file_binary();
	input_file_binary();
	system("pause");
	return 0;
}