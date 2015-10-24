#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

typedef int ValueT;
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
   Node(int i){ dist=INF; idx=i; visited=false;}
};

const int MAX_V = 10005;
Node nodes[MAX_V];
vector<Edge> adjList[MAX_V];
typedef tuple<ValueT, int> State;
inline ValueT dist(const State& s) { return get<0>(s); }
inline int node(const State& s) { return get<1>(s); }

struct MyCompare {
   bool operator() (const State& lhs, const State& rhs) { return dist(lhs) > dist(rhs); }
};

void dijkstra(int start) {
   priority_queue<State, vector<State>, MyCompare> pq;
   pq.push(State(0, start));
   nodes[start].dist = 0;
   while(!pq.empty()) {
      State state = pq.top(); pq.pop();
      if (nodes[node(state)].visited) continue;
      nodes[node(state)].visited = true;
      for (int i = 0; i < (int) adjList[node(state)].size(); ++i){ 
         const Edge& e = adjList[node(state)][i];
         ValueT next_dist = nodes[e.from].dist + e.weight;
         if (next_dist < nodes[e.to].dist) {
            nodes[e.to].dist = next_dist;
            pq.push(State(next_dist, e.to));
         }
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
         adjList[k].clear();
      }
      for (int k = 0; k < m; ++k) {
         int a, b, c; cin >> a >> b >> c;
         adjList[a].push_back(Edge(a, b, c));
      }
      dijkstra(s);
      for (int i = 0; i < q; ++i) {
         int k; cin >> k;
         if (nodes[k].dist == INF) cout << "Impossible" << endl;
         else cout << nodes[k].dist << endl;
      }
   }
}