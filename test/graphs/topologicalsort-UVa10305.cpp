#include <iostream>
#include <vector>
using namespace std;

typedef int ValueT;
const ValueT INF = 1<<29;

struct Edge {
	int from, to;
	ValueT weight;
	Edge(){from=-1; to=-1; weight=INF;}
	Edge(int a, int b, ValueT c) {from=a; to=b; weight=c;}
};

struct Node {	
	ValueT dist; 
	int idx;
	bool visited;
	Node(int i=-1, int d=INF){ dist=d; idx=i; visited=false;}
};

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

void solve(int n, int m) {
	vector<Node> nodes;
	for (int i = 0; i < n; ++i) {
		nodes.push_back(Node(i, 0));
	}
	vector<vector<Edge> > edges(n);
	for (int i = 0; i < m; ++i) {
		int from, to; cin >> from >> to;
		from--; to--; // For 0-indexing
		Edge edge = Edge(from, to, 0);
		edges[from].push_back(edge);
		nodes[to].dist++;
	}
	vector<Node> visitOrder = topologicalSort(nodes, edges);
	for (Node& n : visitOrder) {
		cout << n.idx+1 << " ";
	}
	cout << endl;
}

int main() {
	ios::sync_with_stdio(false);
	int n, m; cin >> n >> m;
	for(;n != 0; cin >> n >> m) {
		solve(n, m);
	}
}