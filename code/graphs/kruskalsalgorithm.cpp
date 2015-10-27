vector<Edge> mst(vector<Edge>& edges, int numNodes) {
	priority_queue<Edge, vector<Edge>, EdgeCmp> q(edges.begin(), edges.end());  
	UnionFind u(numNodes);
	vector<Edge> ret;

	while (!q.empty()) {
		Edge e = q.top(); q.pop();
		if (u.same(e.to, e.from)) {
			u.join(e.to, e.from);
			ret.push_back(e);
			if ((int) ret.size() == numNodes - 1) return ret;
		}
	}
	
	return ret;
}