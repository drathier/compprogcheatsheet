void update(vector<vector<T>> &tree, int i, int k, T amount) {
	for (; i < tree.size(); i |= i + 1) {
		for (int p = k; p < tree[i].size(); p |= p + 1) {
			tree[i][p] += amount;
		}
	}
}

T sum(const vector<vector<T>> &tree, int i, int k) {
	T s = T();
	for (; i > 0; i &= i - 1) {
		for (int p = k; p > 0; p &= p - 1) {
			s += tree[i - 1][p - 1];
		}
	}
	return s;
}