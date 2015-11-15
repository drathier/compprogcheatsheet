#include <vector>
#include <assert.h>
#include <iostream>
#include <climits>

using namespace std;

using T = long long;
using Row = vector<T>;
using Matrix = vector<Row>;

void matmul(Matrix &a, Matrix &b, Matrix &out, T mod = LLONG_MAX / 2) { // assuming (row,col) and a.size = b[0].size()
	for (int i = 0; i < a.size(); i++) {
		for (int k = 0; k < b[0].size(); k++)
			out[i][k] = 0; // reset
		for (int h = 0; h < b.size(); h++) {
			for (int k = 0; k < b[0].size(); k++) {
				out[i][k] = (out[i][k] + a[i][h] * b[h][k]) % mod; // loop order important for cache hits
			}
		}
	}
}

void matpow(Matrix &a, T n, Matrix &out, T mod = LLONG_MAX / 2) { // out=(a^n)%mod assuming square matrix and out filled with zeroes.
	for (int i = 0; i < out.size(); i++)
		out[i][i] = 1; // out = identity matrix
	Matrix tmp(a.size(), Row(a[0].size()));
	while (n > 0) {
		if (n & 1) {
			matmul(out, a, tmp, mod);
			for (int i = 0; i < tmp.size(); i++)
				for (int k = 0; k < tmp[0].size(); k++)
					out[i][k] = tmp[i][k];
		}
		matmul(a, a, tmp, mod);
		for (int i = 0; i < tmp.size(); i++)
			for (int k = 0; k < tmp[0].size(); k++)
				a[i][k] = tmp[i][k];
		n = n / 2;
	}
}

void print(Matrix &a) {
	for (int i = 0; i < a.size(); i++) {
		for (int k = 0; k < a[i].size(); k++) {
			cout << a[i][k] << " ";
		}
		cout << endl;
	}
}

/*
 * not handled:
 * mul of matrix of invalid sizes
 *
 * tested:
 * basic matmul
 * basic matpow for fib(n)
 *
 * not tested:
 * mod
 *
 * todo:
 * short text about how to find the matrix to exponentiate
 * */

int main() {
	Matrix a({{1, 2, 3},
						 {4, 5, 6}});
	Matrix b({{7,  8},
						 {9,  10},
						 {11, 12}});
	Matrix ab({{58,  64},
						  {139, 154}});
	Matrix out(b[0].size(), Row(a.size()));
	matmul(a, b, out);
	assert(out == ab);
	matmul(a, b, out);
	assert(out == ab);

	// matpow test: fibonacci
	Matrix fib({{1, 1},
						   {1, 0}});
	Matrix res({{0, 0},
						   {0, 0}});
	T n = 13;
	matpow(fib, n - 2, res);
	assert(res[0][0] == 144);
	return 0;
}
