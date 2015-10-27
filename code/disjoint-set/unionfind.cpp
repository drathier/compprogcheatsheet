struct UnionFind {
	vector<int> parent;
	vector<int> rank;
	
	UnionFind(int size) {
		for (int i = 0; i < size; ++i) {
			parent.push_back(i);
			rank.push_back(0);
		}
	}
	
	int root(int i) {
		if (parent[i] != i)
			parent[i] = root(parent[i]);
		return parent[i];
	}
	
	bool join(int i, int j) {
		int p = root(i), q = root(j);
		if (p == q) return false;
		if (rank[p] < rank[q]) {
			parent[p] = q;			
		} else if (rank[p] > rank[q]) {
			parent[q] = p;
		} else {
			parent[q] = p;
			rank[q]++;
		}
		return true;
	}
	
	bool same(int i, int j) {
		return root(i) == root(j);
	}
};