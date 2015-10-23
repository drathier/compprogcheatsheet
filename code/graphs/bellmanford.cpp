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
