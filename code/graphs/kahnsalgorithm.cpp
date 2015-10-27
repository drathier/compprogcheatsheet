/* Node.dist is used as an "incoming edges"-counter */
vector<Node> topologicalSort(vector<Node>& nodes, vector<vector<Edge> >& adjList) {
	vector<Node> ret;
	for (Node& n : nodes) {
		if (n.dist == 0) {
			ret.push_back(n);
		}
	}
	for (int i = 0; i < (int) nodes.size(); ++i) {
		Node& n = ret[i];
		for (Edge& e : adjList[n.idx]) {
			nodes[e.to].dist--;
			if (nodes[e.to].dist == 0) ret.push_back(nodes[e.to]);
		}
	}
	return ret;
}