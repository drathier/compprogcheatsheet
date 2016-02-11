#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

struct UnionFind {
   vi parent;
   vi rank;
	
   UnionFind(int size) {
      for (int i = 0; i < size; ++i) {
         parent.push_back(i);
         rank.push_back(0);
      }
   }
	
   int root(int i) {
      if (parent[i] != i)
         parent[i] = root(parent[i]);
      return parent[i];
   }
	
   bool join(int i, int j) {
      int p = root(i), q = root(j);
      if (p == q) return false;
      if (rank[p] < rank[q]) {
         parent[p] = q;			
      } else if (rank[p] > rank[q]) {
         parent[q] = p;
      } else {
         parent[q] = p;
         rank[q]++;
      }
      return true;
   }
	
   bool same(int i, int j) {
      return root(i) == root(j);
   }
};

int main() {
   ios::sync_with_stdio(false);
   int n, l; cin >> n >> l;
   UnionFind u(l+1);
   vi empty_boxes(l+1, 1);
   for (int i = 0; i < n; ++i) {
      int a, b; cin >> a >> b;
      if (!u.same(a, b)) {
         int sum = empty_boxes[u.root(a)] + empty_boxes[u.root(b)];
         u.join(a, b);
         empty_boxes[u.root(a)] = sum;
      }
      if (empty_boxes[u.root(a)]) {
         empty_boxes[u.root(a)]--;
         cout << "LADICA" << endl;
      } else {
         cout << "SMECE" << endl;
      }
   }
}
