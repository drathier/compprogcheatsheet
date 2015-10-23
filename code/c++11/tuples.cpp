#include <tuple>
#include <iostream>
typedef tuple<int, int, int> Tuple;
using namespace std;
int main() {
	Tuple t = Tuple(1, 2, 3);
	cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << endl;
	return 0;
}
