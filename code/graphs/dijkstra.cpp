const int MAX_V = 10005;
Node nodes[MAX_V];
vector<Edge> adjList[MAX_V];
typedef pair<ValueT, int> State;
inline ValueT dist(const State& s) { return s.first; }
inline int node(const State& s) { return s.second; }

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
