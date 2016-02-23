/* Solves UVA 11297 using a 2D SegmentTree*/
#include <cstdio>
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

using Int = int;
const int MAXN = 505;
Int Map[MAXN][MAXN];
int N;

void readMap() {
   for (int x = 1; x <= N; ++x) {
      for (int y = 1; y <= N; ++y){
         cin >> Map[x][y];
      }
   }
}

using MaxMin = pair<Int, Int>;

struct Node {
   int x, y;
   Int min_value, max_value;
   bool undef;

   Node() {}
   Node(int a, int b, int val, bool undef=false) {
      if (!undef)
         x = a; y = b; min_value = max_value = val;
      this -> undef = undef;
   }

   void revalue(const Node& other) {
      if (!other.undef) {
         if (undef) {
            min_value = other.min_value;
            max_value = other.max_value;
            undef = false;
         } else {
            min_value = min(min_value, other.min_value);
            max_value = max(max_value, other.max_value);
         }
      }
   }
};


struct SegmentTree {
   Node nodes[2 * MAXN * MAXN];

   SegmentTree() {}

   void build() {
      build(1, 1, 1, N, N);
   }

   Node build(int node, int a1, int b1, int a2, int b2, int level=0) {
      if (a1 > a2 or b1 > b2)
         return def();

      if (a1 == a2 and b1 == b2)
         return nodes[node] = Node(a1, b1, Map[a1][b1]);

      nodes[node] = def();
      nodes[node].revalue(build(4 * node - 2, a1, b1, (a1+a2)/2, (b1+b2)/2, level+1));
      nodes[node].revalue(build(4 * node - 1, (a1+a2)/2+1, b1, a2, (b1+b2)/2, level+1));
      nodes[node].revalue(build(4 * node + 0, (a1+a2)/2+1, (b1+b2)/2+1, a2, b2, level+1));
      nodes[node].revalue(build(4 * node + 1, a1, (b1+b2)/2+1, (a1+a2)/2, b2, level+1));
      return nodes[node];
   }

   MaxMin query(int x1, int y1, int x2, int y2) {
      Node best = _query(1, 1, 1, N, N, x1, y1, x2, y2);
      return MaxMin(best.max_value, best.min_value);
   }

   Node _query(int node, int a1, int b1, int a2, int b2, int x1, int y1, int x2, int y2, int level=0, char c='a') {
      if (x1 > a2 or y1 > b2 or x2 < a1 or y2 < b1 or a1 > a2 or b1 > b2)
         return def();

      if (x1 <= a1 and y1 <= b1 and a2 <= x2 and b2 <= y2) {
         return nodes[node];
      }

      Node ret = def();
      ret.revalue(_query(4 * node - 2, a1, b1, (a1+a2)/2, (b1+b2)/2, x1, y1, x2, y2, level+1, 'a'));
      ret.revalue(_query(4 * node - 1, (a1+a2)/2+1, b1, a2, (b1+b2)/2, x1, y1, x2, y2, level+1, 'b'));
      ret.revalue(_query(4 * node + 0, (a1+a2)/2+1, (b1+b2)/2+1, a2, b2, x1, y1, x2, y2, level+1, 'c'));
      ret.revalue(_query(4 * node + 1, a1, (b1+b2)/2+1, (a1+a2)/2, b2, x1, y1, x2, y2, level+1, 'd'));
      return ret;
   }

   void update(int x, int y, int c) {
      _update(1, 1, 1, N, N, x, y, c);
   }

   Node _update(int node, int a1, int b1, int a2, int b2, int x, int y, int val, int level=0) {
      if (a1 > a2 or b1 > b2)
         return def();

      if (x > a2 or y > b2 or x < a1 or y < b1)
         return nodes[node];

      if (x == a1 and y == b1 and x == a2 and y == b2)
         return nodes[node] = Node(x, y, val);

      Node ret = def();
      ret.revalue(_update(4 * node - 2, a1, b1, (a1+a2)/2, (b1+b2)/2, x, y, val, level+1));
      ret.revalue(_update(4 * node - 1, (a1+a2)/2+1, b1, a2, (b1+b2)/2, x, y, val, level+1));
      ret.revalue(_update(4 * node + 0, (a1+a2)/2+1, (b1+b2)/2+1, a2, b2, x, y, val, level+1));
      ret.revalue(_update(4 * node + 1, a1, (b1+b2)/2+1, (a1+a2)/2, b2, x, y, val, level+1));
      return nodes[node] = ret;
   }

   Node def() {
      return Node(0, 0, 0, true);
   }

};


SegmentTree st;
int main() {
   cin >> N;
   readMap();
   st.build();

   int Q; cin >> Q;
   while (Q--) {
      char tmp; cin >> tmp;
      if (tmp == 'c') {
         int a, b, c;
         cin >> a >> b >> c;
         st.update(a, b, c);
      } else if (tmp == 'q') {
         int a, b, c, d;
         cin >> a >> b >> c >> d;
         MaxMin mm = st.query(a, b, c ,d);
         cout << mm.first << " " << mm.second << endl;
      }
   }
}

