const int INF = 1<<31; 
const int MAX_V = 101;
const int MAX_E = 10000;
int dist[MAX_V][MAX_V];
Edge edges[MAX_E];
void floydWarshall(int size, int num_edge) {
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			dist[i][j] = INF;
	for (int k = 0; k < size; ++k) {dist[k][k] = 0;}
	for (int e = 0; e < num_edge; ++e) {
		Edge e = edges[e];
		dist[e.from][e.to] = min(dist[e.from][e.to], e.weight);
	}
	for (int k = 0; k < size; ++k) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; ++j) {				
				if (dist[i][k] == INF || dist[k][j] == INF) continue;
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
				/* If solving with negative cycles copy this loop and change the above line to
					'if (dist[k][k] < 0) dist[i][j] = -INF;'*/
			}
		}
	}
}
