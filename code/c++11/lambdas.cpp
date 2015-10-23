#include <function>
#include <iostream>

using namespace std;

int main(){
	function<void(int, int)> prnt = [](int a, int b){cout << a << " and " << b << endl;}
	int the_int = 42;
	function<void(int)> prnt2 = [&the_int](int a){cout << a << " THE_INT: " << the_int << endl;}
	int leet = 1337;
	function<void()> prnt3 = [&](){cout << the_int << " vs. " << leet << endl;}
}
