#include <bits/stdc++.h>
using namespace std;

using ValueT = long long;
const ValueT INF = 1<<29;

struct Edge {
	int from, to;
	ValueT weight;
	Edge(int a, int b, ValueT c) {from=a; to=b; weight=c;}
};

struct Node {	
	ValueT dist; 
	int idx;
	bool visited;
	Node() {dist=INF; idx=-1; visited=false;}
	Node(int i) {dist=INF; idx=i; visited=false;}
};
using T = long long;
using vi=vector< int >;
using vvi=vector< vi >;

/** It is important to create the adjecency list with bidirectional edges */

const int UNDEF = -1;

int SINK = UNDEF;
int SOURCE = UNDEF;

bool has_aug_path(vvi& flow_graph, vvi& adjacency_list, vi& parent) {
   vvi& adj = adjacency_list;

   int s = SOURCE, t = SINK;
   vector<bool> visited(flow_graph.size(), false);
   queue<int> q;
   q.push(s);
   parent[s] = UNDEF;
   visited[s] = true;

   while (!q.empty()) {
      int now = q.front(); q.pop();

      for (int neighbour : adj[now]) {
	 const int n = neighbour;
	 if (!visited[n] && flow_graph[now][n] > 0) {
	    parent[n] = now;
	    visited[n] = true;
	    q.push(n);
	    if (n == t) {
	      return true;
	    }
	 }
      }
   }

   return false;
}

vvi added_flow;

// Flow graph == Residual graph with capacities applied
int max_flow(vvi& flow_graph, vvi& adjacency_list, int source, int sink) {
   for (int i = 0; i < flow_graph.size(); ++i) {
      added_flow.push_back(vi());
      for (int k = 0; k < flow_graph[i].size(); ++k) 
         added_flow[i].push_back(0);
   }
   SOURCE = source;
   SINK = sink;
   vi parent(flow_graph.size());
   
   int maximum = 0;
   while (has_aug_path(flow_graph, adjacency_list, parent)) {
      int flow = INF;
      
      // Search through path for limiting flow
      for (int current = SINK; current != SOURCE; current = parent[current]) {
	 int p = parent[current];
	 flow = min(flow, flow_graph[p][current]);
      }

      // Fill path with limiting flow
      for (int current = SINK; current != SOURCE; current = parent[current]) {
	 int p = parent[current];
         added_flow[p][current] += flow;
         added_flow[current][p] -= flow;
	 flow_graph[p][current] -= flow;
	 flow_graph[current][p] += flow;
      }

      maximum += flow;
   }

   return maximum;
}


int main() {
   ios::sync_with_stdio(false);
   int n, m, s, t;
   cin >> n >> m >> s >> t;
   vvi flow;
   vvi adj;
   for (int i = 0; i < n; ++i) {
      flow.push_back(vi());
      for (int k = 0; k < n; ++k) {
         flow[i].push_back(0);
      }
      adj.push_back(vi());
   }
   
   for (int i = 0; i < m; ++i) {
      int u, v, c;
      cin >> u >> v >> c;
      flow[u][v] = c;
      adj[u].push_back(v);
      adj[v].push_back(u);
   }
   int total_flow = max_flow(flow, adj, s, t);

   cout << n << " " << total_flow << " ";
   int num_edges = 0;
   vector<tuple<int, int> > ans;
   for (int r = 0; r < n; ++r) {
      for (int c = 0; c < n; c++) {
         if (added_flow[r][c] > 0)  {
            num_edges++;
            ans.push_back(tuple<int, int>(r, c));
         }
      }
   }
   cout << num_edges << endl;
   for (tuple<int, int> t : ans) {
      int u = get<0>(t), v = get<1>(t);
      cout << u << " " << v << " " << added_flow[u][v] << endl;
   }
}
