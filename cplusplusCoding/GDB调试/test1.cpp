#include <iostream>
using namespace std;

int test_0(int a);
//gdb测试用
int main(){
    int a = 0;
    while(a<100){
        a = test_0(a);
    }
    cout<<"a: "<<a<<endl;
    return 0;
}

int test_0(int a){
    return a + 10;
}