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
   Node() {dist=INF; idx=-1; visited=false;}
   Node(int i){ dist=INF; idx=i; visited=false;}
};

const int MAX_V = 1005;
const int MAX_E = 5005;
Node nodes[MAX_V];
Edge edgeList[MAX_E];

void bellmanFord(int start, int num_nodes, int num_edges) {
   nodes[start].dist = 0;
   for (int i = 1; i < num_nodes; ++i) {
      for (int k = 0; k < num_edges; ++k) {
         const Edge& e = edgeList[k];
         if (nodes[e.from].dist != INF)
            nodes[e.to].dist = min(nodes[e.to].dist, nodes[e.from].dist + e.weight);
      }
   }
    
   for (int i = 1; i < num_nodes; ++i) {
		for (int k = 0; k < num_edges; ++k) {
			const Edge& e = edgeList[k];
			if (nodes[e.from].dist == INF) continue;
			  
			ValueT dist = nodes[e.from].dist + e.weight;
			ValueT other = nodes[e.to].dist;
			  
			if (dist < other)
				nodes[e.to].dist = -INF;
		}   
	}
}

int main() {
   ios::sync_with_stdio(false);
   int n, m, q, s;
   cin >> n >> m >> q >> s;
   int first = 0;
   for (; n != 0; cin >> n >> m >> q >> s) {
		if (first++ != 0)
         cout << endl;
      for (int k = 0; k < n; ++k) {
         nodes[k] = Node(k);
      }
      for (int k = 0; k < m; ++k) {
         int a, b, c; cin >> a >> b >> c;
         edgeList[k] = Edge(a, b, c);
      }
      bellmanFord(s, n, m);
      for (int i = 0; i < q; ++i) {
         int k; cin >> k;
         if (nodes[k].dist == INF) cout << "Impossible" << endl;
         else if (nodes[k].dist == -INF) cout << "-Infinity" << endl;
         else cout << nodes[k].dist << endl;
      }
        
   }
}