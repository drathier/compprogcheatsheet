#include <bits/stdc++.h>
using namespace std;
using T = long long;
using vi=vector< int >;
using vvi=vector< vi >;

/** It is important to create the adjecency list with bidirectional edges*/

const int INF = 100000;
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

// Flow graph == Residual graph with capacities applied
int max_flow(vvi& flow_graph, vvi& adjacency_list, int source, int sink) {
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
	 flow_graph[p][current] -= flow;
	 flow_graph[current][p] += flow;
      }

      maximum += flow;
   }

   return maximum;
}
