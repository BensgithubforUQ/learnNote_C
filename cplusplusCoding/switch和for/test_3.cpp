#include<iostream>
#include<string>

using namespace std;

//int main() {
//	int typedef weight;
//	int size = 0;
//	cout << "please input pig amount" << endl;
//	cin >> size;
//	weight *pig = new int[size];
//	int i = 0,heaviestPig = 0;
//	cout << "please input pig weight(ctrl+z to pause in advance)" << endl;
//	while (cin >> pig[i] && i<size) {
//		if (i > 0) {
//			if (pig[i] > pig[heaviestPig]) {
//				heaviestPig = i;
//			}
//		}
//		i++;
//		if (i >= size) {
//			break;
//		}
//	}
//	cout << "the heaviest pig is the" << heaviestPig + 1<< endl;
//	return 0;
//}

//用三目运算符改写上述代码,并且输出最重的体重。
//int main() {
//	int typedef weight;
//	int size = 0;
//	cout << "please input pig amount" << endl;
//	cin >> size;
//	weight* pig = new weight[size];
//	int i = 0, heaviestPig = i;
//	cout << "please input pigs' weight" << endl;
//	while (cin >> pig[i] && i < size) {
//		if (i > 0) {
//			heaviestPig = pig[i - 1] ? pig[i] : pig[i] > pig[i - 1];
//		}
//		i++;
//	}
//	cout << "the heaviest pig is " << heaviestPig<<"kg";
//	return 0;
//}

//switch 用法，switch相比if，结构更清晰，效率更高，但是只能用于整型或者字符型变量。
//int main() {
//	int score = 0;
//	
//	cout << "please evaluate the film" << endl;
//	cin >> score;
//	switch (score)
//	{
//	case 10 :
//		cout << "it is a fantastic film" << endl;
//		break;
//	case 9:
//		cout << "it is a fantastic film" << endl;
//		break;
//	case 8:
//		cout << "it is a pretty good film" << endl;
//		break;
//	case 7:
//		cout << "it is a good film" << endl;
//		break;
//	case 6:
//		cout << "it is a normal film" << endl;
//		break;
//	case 5:
//		cout << "it is not a bad film" << endl;
//		break;
//	default:
//		cout << "this film is no good" << endl;
//		break;
//	}
//	return 0;
//}

//string的特性，中间不能带空格。
//int main() {
//	string str;
//	cin >> str;//从键盘读入str，遇到空格就停了、
//	//fflush(stdin);
//	cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
//	//这行代码用于清除cin缓冲区中的数据。
//	cout <<"str is "<< str << endl;
//	string str1 = "132456wbm 132";//拷贝初始化
//	cout << "str1 is " << str1 << endl;
//
//	string str2;
//	cin >> str >> str2;
//	//fflush(stdin);
//	cout << "str2 is " << str << str2 << endl;
//	string str3("value");//直接初始化
//	string str4(10, 'c');//直接初始化
//	cout << "str3 is " << str3 << endl;
//	cout << "str4 is " << str4 << endl;
//	//如果想用string读取包括空格的一整行，用getline()
//	string line,line1;
//	int i = 0;
//	while (getline(cin, line)) {
//		if (!line.empty() && line.size() > 5) { //line.size()>5的意思是输出大于5的行
//			cout << "line is " << line << endl;
//		}
//		if (i == 0) {
//			line1 = line;
//		}
//		else {
//			if (line > line1) {
//				line1 = line;
//				cout << "the bigger line is:" << line1 << endl;
//			}
//			else if (line == line1) {
//				cout << " the two line is same" << endl;
//			}
//			else {
//				cout << "the bigger line is:" << line1 << endl;
//			}
//		}
//		i++;
//	}
//	string finalStr = str + str1 + str2 + str3 + str4 + line + line1;
//	cout << "the final string is :" << finalStr << endl;
//	return 0;
//}

//猜数字游戏，while的运用。
//#include <ctime>
//int main() {
//	int number = 0,i = 5,target = 0;
//	
//	srand((unsigned int)time(NULL));
//	target = rand() % 100 + 1;
//	//上面这个代码是c++的随机数写法
//
//	cout << "请开始猜数字，一共有五次机会" << endl;
//	while (i && cin >> number) {
//		if (number > target) {
//			
//			i--;
//			cout << "猜大了,还有" <<i<<"次机会" << endl;
//		}
//		else if (number < target) {
//			i--;
//			cout << "猜小了,还有" << i << "次机会" << endl;
//		}
//		else {
//			cout << "猜对了，一共用了" <<5-i+1<<"次机会" << endl;
//		}
//		if (i == 0) {
//			cout << "机会用完了，失败了,正确答案是" <<target<< endl;
//		}
//
//	}
//	return 0;
//}

//int main() {
//	//输出0 - 9 
//	//do while的区别是先执行一次，再判断条件，和while的区别在于while在于首先就判断一次条件。
//	//比如num直接等于10的时候，也会执行一次，打印10；
//	int num = 10;
//	do {
//		cout << num++ << endl;
//	} while (num < 10);
//	system("pause");
//	return 0;
//}

//水仙花数

//int main() {
//	int num = 100;
//	int b, t, h;
//	while (num < 1000) {
//		h = num / 100;
//		t = (num - h * 100) / 10;
//		b = num % 10;
//		if(b*b*b + t*t*t + h*h*h == num){
//			cout << num << " is a 水仙花 数" << endl;
//		}
//		num++;
//	}
//}

//检查字符串中的标点符号
//int main() {
//	string s;
//	
//	cout << "please input string:" << endl;
//	
//	decltype(s.size()) cnt = 0;
//	while(getline(cin, s)){
//		for (auto c : s) {
//			if (ispunct(c)) {
//				cnt++;
//			}
//		}
//		cout << cnt << " punctuation characters in " << s << endl;
//	}
//	return 0;
//}


//将字符串中所有的小写字母变成大写字母
//int main() {
//	string s;
//	cout << "please input string:" << endl;
//	decltype(s.size()) cnt = 0;
//	while (getline(cin, s)) {
//		for (auto& c : s) {
//			if (isalpha(c)) {
//				c = toupper(c);
//			}
//		}
//		cout <<"the upper string is " << s << endl;
//	}
//	return 0;
//}



//敲桌子游戏
//int main() {
//	for (int i = 0; i <= 100;i++) {
//		if (i == 7 || i % 10 == 7 || i / 10 == 7 || i%7 == 0) {
//			cout << i << " 敲桌子" << endl;
//		}
//		else cout << i << " ";
//	}
//	return 0;
//}

//int main() {
//	string s = "abcasdasdaw!!!!!";
//	cout << s << endl;
//	for (auto &c : s) {
//		c = 'x';
//	}
//	cout << s << endl;
//	const string s1 = "keep out!";
//	for (auto& c : s1) {
//
//	}
//	cout << s1 << endl;
//	string s2("something is strange");
//	if (!s2.empty()) {
//		s2[0] = toupper(s2[0]);
//	}
//	for (decltype(s2.size()) index = 0; index != s2.size() && !isspace(s2[index]); ++index) {
//		s2[index] = toupper(s2[index]);
//	}
//	cout << s2 << endl;
//	return 0;
//}