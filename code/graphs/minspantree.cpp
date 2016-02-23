#include <bits/stdc++.h>
/**
 * Needs union find for its implementation.
 */

/**
 * Interface
 */
class DisjointSet {
public:
    DisjointSet(int size);

    void join(int a, int b);
    int findRoot(int i);
    bool sameSet(int a, int b);

private:
    std::vector<int> parent;
    std::vector<int> rank;
};

/**
 * Implementation
 */
DisjointSet::DisjointSet(int size) {
    parent = std::vector<int>(size);
    rank = std::vector<int>(size);
    for (int i = 0; i < size; ++i) {
        parent[i] = i;
    }
}

int DisjointSet::findRoot(int i) {
    return i != parent[i] ? (parent[i] = findRoot(parent[i])) : parent[i];
}

void DisjointSet::join(int a, int b) {
    int i = findRoot(b), j = findRoot(a);
    if (i != j) {
        if (rank[i] > rank[j]) {
            parent[j] = i;
        } else {
            parent[i] = j;
        }
        if (rank[i] == rank[j]) rank[i]++;
    }
}

inline bool DisjointSet::sameSet(int a, int b) {
    return findRoot(a) == findRoot(b);
}

using namespace std;

using ValueT=double;
struct Edge {
    int u, v;
    ValueT w;
};
using ve = vector<Edge>;

bool edge_compare(const Edge& lhs, const Edge& rhs) {
    return lhs.w < rhs.w;
}

tuple<ve, ValueT> solve(ve& edges, int nodes) {
    sort(edges.begin(), edges.end(), edge_compare);
    ve tree;
    DisjointSet ds(nodes);
    ValueT sum = 0;
    for (Edge e : edges) {
        if (!ds.sameSet(e.u, e.v)) {
            ds.join(e.u, e.v);
            tree.push_back(e);
            sum += e.w;
        } else if (tree.size() == nodes - 1) {
            break;
        }
    }
    return tuple<ve, ValueT>{tree, sum};
}
