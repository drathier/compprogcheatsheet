#include <assert.h>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

typedef string T;

// does not deduplicate input
// wastes space; stores n pointers per insert
// leaks memory
struct trie {
	trie *next[256] = {};
	vector<T *> things;

	void insert(string s, int p, T *thing) {
		this->things.push_back(thing);
		if (next[s[p]] == nullptr)
			next[s[p]] = new trie();
		if (p < s.size())
			next[s[p]]->insert(s, p + 1, thing);
	}

	vector<T *> find(string s, int p) {
		if (p == s.size())
			return things;
		if (next[s[p]] != nullptr)
			return next[s[p]]->find(s, p + 1);
		return vector<T *>();
	}
};


int main() {
	trie t;
	T seven = "7";
	T two = "2";
	T sixteen = "16";
	T fourtytwo = "42";
	T thirtyseven = "37";
	t.insert("hejsan", 0, &seven);
	t.insert("hejsan", 0, &two);
	t.insert("hejsan", 0, &sixteen);
	t.insert("hej", 0, &fourtytwo);
	t.insert("hejsan", 0, &seven); // again
	t.insert("hej", 0, &thirtyseven);
	assert(t.find("", 0) == vector<T *>({&seven, &two, &sixteen, &fourtytwo, &seven, &thirtyseven}));
	assert(t.find("hej", 0) == vector<T *>({&seven, &two, &sixteen, &fourtytwo, &seven, &thirtyseven}));
	assert(t.find("hejs", 0) == vector<T *>({&seven, &two, &sixteen, &seven}));
	assert(t.find("hejsan", 0) == vector<T *>({&seven, &two, &sixteen, &seven}));
	assert(t.find("heja", 0) == vector<T *>());
	assert(t.find("", 4711) == vector<T *>());
	assert(t.find("heja", 0) != vector<T *>({&sixteen}));

	trie t2;
	assert(t2.find("", 0) == vector<T *>());
	assert(t2.find("", 4711) == vector<T *>());
	assert(t2.find("hej", 0) == vector<T *>());
}