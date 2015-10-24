#include <tuple>
#include <iostream>
using namespace std;
typedef tuple<int, int, int> Tuple;
int main() {
	Tuple t = Tuple(1, 2, 3);
	cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << endl;
	return 0;
}
