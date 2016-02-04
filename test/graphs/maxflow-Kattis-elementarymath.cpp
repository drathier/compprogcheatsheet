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

namespace problem {

   void solve_kattis() {
      int n; cin >> n;
      vector<T> l(n), r(n);
      vvi flow((4*n) + 2, vector<int>((4*n) + 2));
      vvi adj_list((4*n) + 2);

      int source = 4*n;
      int sink = 4*n + 1;

      map<T, int> to_id;
      int id = n;
      auto add_to_graph = [&](T val) {
	 if (to_id.find(val) == to_id.end()) 
	    to_id[val] = id++;
      };

      for (int i = 0; i < n; ++i) {
	 cin >> l[i] >> r[i];
	 T add = l[i] + r[i], sub = l[i] - r[i], mul = l[i] * r[i];

	 add_to_graph(add);
	 add_to_graph(sub);
	 add_to_graph(mul);

	 flow[source][i] = 1;
	 adj_list[source].push_back(i);
	 adj_list[i].push_back(source);

	 vector<int> vals{to_id[add], to_id[sub], to_id[mul]};

	 for (int v : vals) {
	    adj_list[i].push_back(v);
	    adj_list[v].push_back(i);
	    adj_list[v].push_back(sink);
	    adj_list[sink].push_back(v);
	    flow[i][v] = 1, flow[v][sink] = 1;
	 }
      }

      int maximum_flow = max_flow(flow, adj_list, source, sink);
      set<int> rhs;

      for (int i = 0; i < n; ++i) {
	T add = l[i] + r[i], sub = l[i] - r[i], mul = l[i] * r[i];
	int cnt = 0;
	if (flow[i][to_id[add]] == 0) rhs.insert(i), cnt++;
	if (flow[i][to_id[mul]] == 0) rhs.insert(i), cnt++;
	if (flow[i][to_id[sub]] == 0) rhs.insert(i), cnt++;
      }

      if (maximum_flow == n) {
	 for (int i = 0; i < n; ++i) {
	    T add = l[i] + r[i], sub = l[i] - r[i], mul = l[i] * r[i];
	    if (flow[to_id[add]][i] != 0) {
	       cout << l[i] << " + " << r[i] << " = " << add << endl;
	    } else if (flow[to_id[sub]][i] != 0) {
	       cout << l[i] << " - " << r[i] << " = " << sub << endl;
	    } else if (flow[to_id[mul]][i] != 0) {
	       cout << l[i] << " * " << r[i] << " = " << mul << endl;
	    }
	 }
      } else {
	 cout << "impossible" << endl;
      }
   }

};


int main() {
   problem::solve_kattis();
}
