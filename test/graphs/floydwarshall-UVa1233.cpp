/**
 * The problem solved is p1233 in UVa:s database.
 * The basic idea is that the usher sends the thing
 * through the same (highest awarding) cycle as many times
 * as possible to get the highest value. Then you remove the number of
 * times that the usher gets the thing back.
 */
#include <iostream>
using namespace std;

constexpr int min(int a, int b) { return a < b ? a : b; }

int solve(int b, int p)
{	
	int capacity = b, parishioners = p;
	int Graph[parishioners+1][parishioners+1];	
	for (int r = 0; r <= parishioners; ++r) {
		for (int c = 0; c <= parishioners; c++) {
			Graph[r][c] = INF;
		}
	}

	int usherEdges; cin >> usherEdges;	
	for (int k = 0; k < usherEdges; k++) {
		int tmp; cin >> tmp;
		Graph[0][tmp] = 0;
	}
	
	// Edges are represented directly in the graph
	for (int i = 1; i <= parishioners; ++i) {
		int edges; cin >> edges;
		for (;edges--;) {
			int cost, to; cin >> cost >> to;
			Graph[i][to] = min(Graph[i][to], cost);
		}
	}	
	
	for (int k = 0; k <= parishioners; ++k) 
		for (int i = 0; i <= parishioners; ++i) 
			for (int j = 0; j <= parishioners; ++j) 
				Graph[i][j] = min(Graph[i][j], Graph[i][k] + Graph[k][j]);
	
	int bestCost = Graph[0][0];
	int answer = 0, current = 0;
	while (true) {
		if ((current += bestCost) >= capacity) break;
		current--;
		answer++;
	}
	
	return answer;
}

int main()
{
	ios::sync_with_stdio(false);
	int TC; cin >> TC;
	while (TC--) {
		int b, p; cin >> b >> p;
		cout << solve(b, p) << endl;
	}
	return 0;
}
