/* Finds the set of strongly connected components. */
struct SCCFinder {
	SCCFinder(){};
	const int UNEXPLORED = -1;
	const int NO_SCC = -1;

	vvi find_sccs(const vvi& adj_list) {
		// Reset
		num_scc = ticks = 0;
		s = stack<int>();
		d = vi(adj_list.size(), UNEXPLORED);
		low = vi(adj_list.size());
		scc = vi(adj_list.size(), NO_SCC);
		in_stack = vector<bool>(adj_list.size(), false);

		// DFS all nodes
		for (int a = 0; a < adj_list.size(); ++a) {
			if (d[a] == UNEXPLORED) tarjan(adj_list, a);
		}

		// Count which scc every node belong to
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

	void tarjan(const vvi& adj_list, int u) {
		d[u] = low[u] = ticks++;
		s.push(u);
		in_stack[u] = true;

		// Visit all neighbours, carry lowlink up
		for (int v : adj_list[u]) {
			if (d[v] == UNEXPLORED) {
				tarjan(adj_list, v);
				low[u] = min(low[u], low[v]);
			} else if (in_stack[v]) {
				low[u] = min(low[u], low[v]);
			}
		}

		// If we are the node that started the lowlink
		// Pop all nodes visited with dfs and add to scc
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

