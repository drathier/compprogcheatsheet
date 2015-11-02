// TODO(Unimplemented)

#include <string>
#include <vector>

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
