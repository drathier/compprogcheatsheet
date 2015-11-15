#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

typedef long long T;

#define rep(a, b, c) = for(__typeof(a) a = b; a < c; ++a)

T det(vector<vector<T>> const &a) { // square matrix
	if (a.size() == 2 && a[0].size() == 2) {
		return a[0][0] * a[1][1] - a[1][0] * a[0][1];
	}
	T ret = 0;
	for (int i = 0; i < a.size(); i++) {
		vector<vector<T>> tmp(a.size() - 1, vector<T>(a.size() - 1));
		for (int p = 1; p < a.size(); p++) {
			for (int k = 0; k < a.size(); k++) {
				if (k == i) continue;
				tmp[p - 1][k - (k > i)] = a[p][k];
			}
		}
		ret += a[0][i] * det(tmp) * ((i % 2) * 2 - 1);
	}
	return ret;
}


int main() {
	vector<vector<T>> a({{1, 2, 3},
						 {4, 5, 6},
						 {7, 8, 9}});
	vector<vector<T>> b({{7, 8},
						 {9, 10}});
	vector<vector<T>> c({{58,  64},
						 {139, 154}});
	vector<vector<T>> out(a.size(), vector<T>(a[0].size()));

	assert(det(a) == 0);
	assert(det(b) == -2);
	assert(det(c) == 36);

	cout << "det(a) " << det(a) << endl;
	cout << "det(b) " << det(b) << endl;
	cout << "det(c) " << det(c) << endl;

	return 0;
}