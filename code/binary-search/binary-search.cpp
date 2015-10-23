#include <iostream>
using namespace std;

int tst[] = {1, 1, 2, 3, 3, 4, 5, 5, 6, 7};

bool lte(int a) {
	return tst[a] <= 0;
}

int search(int n) {
	int i = 0, k = n;
	while (i < k) {
		int m = i + (k - i) / 2;
		cout << "i=" << i << ", m=" << m << ", k=" << k << endl;
		if (lte(m)) { // max(lte(m)) s.t. lte(m) is true
			i = m + 1;
		} else {
			k = m;
		}
	}
	return i; // returns where needle SHOULD be!
}

int main() {
	cout << search(10) << endl;
}