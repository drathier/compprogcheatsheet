int findRoot(vector<int>& parent, int i) {
	if (parent[i] != i) parent[i] = findRoot(parent, parent[i]);
	return parent[i];
}

bool join(vector<int>& parent, int i, int j) {
	int p = findRoot(parent, i), q = findRoot(parent, j);
	if (p != q) {parent[q] = p; return true;}
	return false;
}
