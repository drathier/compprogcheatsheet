#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

using T = long long;
using Row = vector<T>;
using Matrix = vector<Row>;


T det(const Matrix& a) { // square matrix
	if (a.size() == 2 && a[0].size() == 2) {
		return a[0][0] * a[1][1] - a[1][0] * a[0][1];
	}
	T ret = 0;
	for (int i = 0; i < a.size(); i++) {
		Matrix tmp(a.size() - 1, vector<T>(a.size() - 1));
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
	Matrix a({{1, 2, 3},
						 {4, 5, 6},
						 {7, 8, 9}});
	Matrix b({{7, 8},
						 {9, 10}});
	Matrix c({{58,  64},
						 {139, 154}});
	Matrix out(a.size(), Row(a[0].size()));

	assert(det(a) == 0);
	assert(det(b) == -2);
	assert(det(c) == 36);

	return 0;
}
