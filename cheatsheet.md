#Cheatsheet - Programming

## Best Complexity
*Assuming 10<sup>6</sup> items in 1 s with 3s Time Limit*

<table>
	<tr>
		<td>N</td>
		<td>Worst AC Algorithm</td>
		<td>Comment</td>
	</tr>
	<tr>
		<td><= 10</td>
		<td>O(n!), O(n^6)</td>
		<td>Enumerating a permutation</td>
	</tr>
	<tr>
		<td><= 15</td>
		<td>O(2<sup>n</sup> * n<sup>2</sup>)</td>
		<td>TSP with DP</td>
	</tr>
	<tr>
		<td><= 20</td>
		<td>O(2<sup>n</sup>), O(n<sup>5</sup>)</td>
		<td>DP + bitmask</td>
	</tr>
	<tr>
		<td><= 50</td>
		<td>O(n<sup>4</sup>)</td>
		<td></td>
	</tr>
	<tr>
		<td><= 100</td>
		<td>O(n<sup>3</sup>)</td>
		<td>Floyd Warshall</td>
	</tr>
	<tr>
		<td><= 1K</td>
		<td>O(n<sup>2</sup>)</td>
		<td>Bubble sort</td>
	</tr>
	<tr>
		<td><= 100K</td>
		<td>O(n log<sub>2</sub> n)</td>
		<td>Merge Sort, Segment Tree</td>
	</tr>
	<tr>
		<td><= 1M</td>
		<td>O(n), O(log<sub>2</sub> n), O(1)</td>
		<td>Max, binarysearch</td>
	</tr>
</table>

# C++11 
## Tuples
Like `std::pair` but arbitrary length. 

	#include <tuple>
	#include <iostream>
	typedef tuple<int, int, int> Tuple;
	using namespace std;
	int main() {
		Tuple t = Tuple(1, 2, 3);
		cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << endl;
		return 0;
	}

## Range Query
If you need to update the `sum(values[i] for i in range(a, b))` many times. <br/>
Both functions run in **O(log<sub>2</sub> n)**.

#### Fenwick Tree
    

	typedef int T;
	void update(vector<T>& tree, int i, T amount) {
		for(; i < (int) tree.size(); i|= i+1) tree[i] += amount;
	}

	T sum(const vector<T>& tree, int i) {
		T s = T();
		for(; i > 0; i &= i-1) s += tree[i-1];
		return s;
	}

## Disjoint-set datastructure
Using union-find datastructure. <br/>
Both functions run in **O(log<sub>2</sub> n)**.

#### Union-find

	int findRoot(vector<int>& parent, int i) {
		if (parent[i] != i) parent[i] = findRoot(parent, parent[i]);
		return parent[i];
	}

	bool join(vector<int>& parent, int i, int j) {
		int p = findRoot(parent, i), q = findRoot(parent, j);
		if (p != q) {parent[q] = p; return true;}
		return false;
	}

## Single Source Shortest Path
Can find shortest path from `a` to `b` in a graph. <br/>
The algorithm used depends on properties of the graph. <br/>
Negative weights in the graph? Use Bellman-Ford. <br/>
Otherwise use Dijkstra.

#### Graph Library
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
		Node(int i) {dist=INF; idx=i; visited=false;}
	};
	

#### Dijkstra - No negative weights
**O(|E| + |V| log |V|)**

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


#### Bellman-Ford implementation (assumes graph library)

Can also find negative cycles in the graph. (nodes that can circle around until -infinity)<br/>
**O(|V| * |E|)**

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

## All Pairs Shortest Path

#### Floyd Warshall
Used both to solve shortest path problems but can also be used to find negative cycles in a graph.<br/>
**O( |V|<sup>3</sup>)**
	
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
	
# Math
General math algorithms.

## Prime Sieve
**O(N sqrt(N))**

	vector<bool> sieve(long limit) {
		vector<bool> sieve(limit+1, true);
		sieve[0] = sieve[1] = false;
		sqlim = sqrt(limit) + 1;
		for (long i = 2; i <= sqlim; ++i) {
			if (sieve[i]) {
				for (long j = i * i; j <= limit; j += i) {
					sieve[j] = false;
				}
			}
		}
		return sieve;
	}

## GCD, LCM, Extended Euclid

	int gcd(int a, int b) {
		if (b == 0) return a;
		return gcd(b, a%b);
	}

	int lcm(int a, int b) {
		return abs(a*b) / gcd(a, b);
	}

	typedef tuple<int, int, int> i3tuple;
	typedef tuple<int, int> i2tuple;

	i3tuple extendedEuclid(int a, int b) {
		if (a == 0) return i3tuple(b, 0, 1);
		Tuple t = extendedEuclid(b % a, a);
		int _gcd = get<0>(t), x = get<1>(t), y = get<2>(t)
		return i3tuple(_gcd, x - (b/a) * y, y);
	}

	i2tuple diophanticEquation(int a, int b, int c) {
		if (c%gcd(a, b) != 0) return i2tuple(-1, -1); // Unsolvable
		i3tuple t = extendedEuclid(a, b);
		int _gcd = get<0>(t), x = get<1>(t), y = get<1>(t);
		y *= c; x *= c;
		return i2tuple(x, y);
	}

# Strings

## Trie *(untested)*

	struct trie {
		int wc = 0; // word count
		int pc = 0; // prefix count
		trie* backtrack[26]; // 26 == size of english alphabet
		trie () { for(int i = 0; i < 26; ++i) backtrack[i] = nullptr; }

		void addWord(const string& str, const string::iterator& it) {
			if (it == str.end()) wc++;
			else {
				char now = *it;
				pc++;
				trie* b = backtrack[now];
				if (b == nullptr)
					b = new trie();
				b->addWord(str, ++it);
			}
		}
	
		int count(const string& s, const string::iterator& it) {
			if (it == s.end()) return wc;
			trie* b = backtrack[*it];
			if (b == nullptr)
				return 0;
			return b->count(s, ++it);
		}
		
		int pcount(const string& s, const string::iterator& it) {
			if (s.end() == it) return pc;
			trie* b = backtrack[*it];
			if (b == nullptr) return 0;
			return b->pcount(s, ++it);
		}
	};