#include <iostream>
#include <assert.h>
#include <functional>
#include <vector>

using namespace std;

vector<int> data{-10, -5, 0, 1, 2, 3, 5, 7, 11, 100, 100, 100, 1000, 10000};
vector<int> data_desc{99, 99, 59, 42, 7, 0, -1, -1};

int search(int n, function<bool(int)> lt) {
	int i = 0, k = n;
	while (i < k) {
		int m = i + (k - i) / 2;
		if (lt(m)) { // max(lt(m)) s.t. lt(m) is true
			i = m + 1;
		} else {
			k = m;
		}
	}
	return i; // returns where needle SHOULD be!
}

int main() {
	assert(search(0, function<bool(int)>([](int a) { return a < 0; })) == 0);
	assert(search(1, function<bool(int)>([](int a) { return a < 1; })) == 1);
	assert(search(1, function<bool(int)>([](int a) { return false; })) == 0);
	assert(search(1, function<bool(int)>([](int a) { return true; })) == 1);
	assert(search(1e9, function<bool(int)>([](int a) { return a < 991; })) == 991);
	assert(search(1e9, function<bool(int)>([](int a) { return false; })) == 0);
	assert(search(1e9, function<bool(int)>([](int a) { return true; })) == 1e9);
	assert(search(data.size(), function<bool(int)>([](int a) { return data.at(a) < -20; })) == 0);
	assert(search(data.size(), function<bool(int)>([](int a) { return data.at(a) < -10; })) == 0);
	assert(search(data.size(), function<bool(int)>([](int a) { return data.at(a) < -9; })) == 1);
	assert(search(data.size(), function<bool(int)>([](int a) { return data.at(a) < -6; })) == 1);
	assert(search(data.size(), function<bool(int)>([](int a) { return data.at(a) < -5; })) == 1);
	assert(search(data.size(), function<bool(int)>([](int a) { return data.at(a) < 3; })) == 5);
	assert(search(data.size(), function<bool(int)>([](int a) { return data.at(a) < 11; })) == 8);
	assert(search(data.size(), function<bool(int)>([](int a) { return data.at(a) < 99; })) == 9);
	assert(search(data.size(), function<bool(int)>([](int a) { return data.at(a) < 100; })) == 9);
	assert(search(data.size(), function<bool(int)>([](int a) { return data.at(a) < 101; })) == 12);
	assert(search(data.size(), function<bool(int)>([](int a) { return data.at(a) < 10000; })) == 13);
	assert(search(data.size(), function<bool(int)>([](int a) { return data.at(a) < 10001; })) == 14);
	assert(search(7, function<bool(int)>([](int a) { return data_desc.at(a) > 7; })) == 4);
	assert(search(1e9, function<bool(int)>([](int a) { return 1e9 - a > 7; })) == 1e9 - 7);
	assert(search(2e9, function<bool(int)>([](int a) { return true; })) == 2e9); // overflow test

	return 0;
}
