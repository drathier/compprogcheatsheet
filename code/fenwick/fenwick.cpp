void update(vector <T> &tree, int i, T amount) {
	for (; i < tree.size(); i |= i + 1) tree[i] += amount;
}

T sum(const vector <T> &tree, int i) {
	T s = T();
	for (; i > 0; i &= i - 1) s += tree[i - 1];
	return s;
}
