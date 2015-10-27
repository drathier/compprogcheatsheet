#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <cmath>
#include <numeric>
using namespace std;

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

struct Node {
	double x, y;
	Node(double a, double b) {x = a; y = b;}
	double dist(Node& other) 
		{return sqrt((x-other.x)*(x-other.x) + (y-other.y)*(y-other.y));}
};

struct Edge {
	int from, to;
	double weight;
	Edge(int a, int b, double c=double()) {
		from = a; to = b; weight = c;
	}
};

struct EdgeCmp {
	bool operator()(Edge& e1, Edge& e2) {
		return e1.weight > e2.weight;
	}
};

vector<Edge> mst(vector<Edge>& edges, int numNodes) {
	priority_queue<Edge, vector<Edge>, EdgeCmp> q(edges.begin(), edges.end());  
	UnionFind u(numNodes);
	vector<Edge> ret;

	while (!q.empty()) {
		Edge e = q.top(); q.pop();
		if (u.join(e.to, e.from)) {
			ret.push_back(e);
			if ((int) ret.size() == numNodes - 1) return ret;
		}
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(false); 
	cout << fixed << setprecision(2);
	int TC; cin >> TC;
	while (TC--) {
		int n; cin >> n;

		vector<Node> nodes;
		for (int i = 0; i < n; ++i) {
			double a, b; cin >> a >> b;
			nodes.push_back(Node(a, b));
		}

		vector<Edge> edges;
		for (int i = 0; i < n; ++i) {
			for (int j = i+1; j < n; ++j) {
				double d = nodes[i].dist(nodes[j]);
				edges.push_back(Edge(i, j, d));
			}
		}
		vector<Edge> myMst = mst(edges, n);
		double sum = accumulate(myMst.begin(), myMst.end(), 0.0,
										[](double a, Edge& now){ return a + now.weight; });		
		cout << sum << "\n\n";
	}
}

