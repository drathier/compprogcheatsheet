#include <iostream>
#include <vector>
#include <stack>
using namespace std;
using vi=vector<int>;
using vvi=vector<vi>;

struct SCCFinder {
  
  SCCFinder(){};
  
  void reset() {
    d.clear();
    low.clear();
    scc.clear();
    while (!s.empty()) s.pop();
    in_stack.clear();
    num_scc = ticks = 0;
  }

  vvi find_sccs(vvi& adj_list) {
    reset();
    d = vi(adj_list.size(), -1);
    low = vi(adj_list.size());
    scc = vi(adj_list.size(), -1);
    in_stack = vector<bool>(adj_list.size(), false);
    for (int a = 0; a < adj_list.size(); ++a) {
      if (d[a] == -1) tarjan(adj_list, a);
    }

    vvi sccs(num_scc);
    for (int i = 0; i < scc.size(); ++i) {
      sccs[scc[i]].push_back(i);
    }
    return sccs;
  }

  int num_scc;
  int ticks;
  vi d, low, scc;
  vector<bool> in_stack;
  stack<int> s;

  void tarjan(vvi& adj_list, int u) {
    d[u] = low[u] = ticks++;
    s.push(u);
    in_stack[u] = true;

    for (int v : adj_list[u]) {
      if (d[v] == -1) {
	tarjan(adj_list, v);
	low[u] = min(low[u], low[v]);
      } else if (in_stack[v]) {
	low[u] = min(low[u], low[v]);
      }
    }

    if (d[u] == low[u]) {
      int v;
      do {
	v = s.top(); s.pop();
	in_stack[v] = false;
	scc[v] = num_scc;
      } while(u != v);
      num_scc++;
    }
  }

};

SCCFinder sf;
int main() {
  int n, m; cin >> n >> m;
  for (; n != 0; cin >> n >> m) {
    vvi adj(n);
    for (int i = 0; i < m; ++i) {
      int a, b, type; cin >> a >> b >> type;
      a--; b--;
      adj[a].push_back(b);
      if (type == 2) adj[b].push_back(a);
    }

    vvi sccs = sf.find_sccs(adj);
    if (sccs.size() == 1) {
      cout << "1" << endl;
    } else {
      cout << "0" << endl;
    }

  }
  
}
