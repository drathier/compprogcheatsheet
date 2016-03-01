#include <bits/stdc++.h>
using namespace std;
// Sometimes you might want to have a map
// instead of a vector because of the number of possible nodes
// are different (see https://open.kattis.com/problems/parallelanalysis)
// In that case the numbers will be integers between [0, 2^31 - 1]
// But this is mostly not the case.
// Change the definition here and wherever deps/adj_list is assigned to.
using vi = vector<int>;
using vvi = vector<vi>;

class Toposorter {
private:
    vi deps;
    vvi adj_list;

public:

    Toposorter(int num_nodes) {
        deps = vi(num_nodes);
        adj_list = vvi(num_nodes);
    };

    void reset() {
        const int num_nodes = deps.size();
        deps = vi(num_nodes);
        adj_list = vvi(num_nodes);
    }

    // e.from has to be done before e.to
    void run(const vector<Edge>& dependencies) {
        for (const Edge& e : dependencies) {
            deps[e.to]++;
            adj_list[e.from].push_back(e.to);
        }
    }
    
    vi topological_order() {
        const int num_nodes = deps.size();
        vi the_deps(deps);
        vi order;

        for (int i = 0; i < num_nodes; ++i) {
            if (the_deps[i] == 0) order.push_back(i);
        }

        for (int i = 0; i < order.size(); ++i) {
            int now = order[i];
            for (int neigh : adj_list[now]) {
                the_deps[neigh]--;
                if (the_deps[neigh] == 0) {
                    order.push_back(neigh);
                }
            }
        }

        return order;
    }

    vi dependencies() {return deps;}
    vvi adjacency_list() {return adj_list;}
};
