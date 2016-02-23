#include <bits/stdc++.h>

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

struct Point {
    double x, y;
    double dist(const Point& o) {
        return sqrt((o.x - x)*(o.x - x) + (o.y - y)*(o.y - y));
    }
};

struct Edge {
    int u, v;
    double w;
};

bool edge_compare(const Edge& lhs, const Edge& rhs) {
    return lhs.w < rhs.w;
}

void solve(vector<Edge>& edges, int nodes) {
    sort(edges.begin(), edges.end(), edge_compare);
    vector<Edge> tree;
    DisjointSet ds(nodes);
    double sum = 0.0;
    for (Edge e : edges) {
        if (!ds.sameSet(e.u, e.v)) {
            ds.join(e.u, e.v);
            tree.push_back(e);
            sum += e.w;
        } else if (tree.size() == nodes - 1) {
            break;
        }
    }
    cout << sum << endl;
}

int main() {
    ios::sync_with_stdio(false);
    int n, islands;
    cout << fixed << setprecision(6);
    cin >> n;
    while (n--) {
        cin >> islands;
        vector<Point> isl(islands);
        for (Point& p : isl) 
            cin >> p.x >> p.y;
        vector<Edge> edges;
        for (int i = 0; i < islands; ++i) {
            for (int k = i+1; k < islands; ++k) {
                edges.push_back(Edge{i, k, isl[i].dist(isl[k])});
            }
        }
        solve(edges, islands);
    }
}
