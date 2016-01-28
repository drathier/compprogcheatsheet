#include <iostream>
#include <vector>
#include <tuple>
#include <map>

using namespace std;
using vi=vector<int>;

// Find the length maximal j such that seq[best[j]] < target
int binary_search(const vi& seq, const vi& best, 
                  int low, int high, int target) {

  for (int middle = (low+high)/2; true; middle=(low+high)/2) {
    if (high - low <= 1) {
      if (seq[best[high]] < target) return high;
      else if (seq[best[low]] < target) return low;
      else return 0; // Nothing is smaller than this (to the left)
    }

    if (seq[best[middle]] < target) low = middle;
    else  high = middle - 1;
  }
}

// Returns the parent vector and the index to the last element in the
// longest sequence.
tuple<vi, int> longest_increasing_subsequence(const vi& seq) {
  int best_length = 1;
  vi current_best(seq.size() + 1);
  current_best[1] = 0;
  vi parent(seq.size());
  for (int i = 0; i < seq.size(); ++i) parent[i] = i;

  // For every number except the first one, find The maximum j such
  // that j < i && seq[j] < seq[i]. We do this by binary searching
  // over the length of the "previous" LIS. We keep a tab on where
  // each longest subsequence is by using the "current_best" vector.

  for (int i = 1; i < seq.size(); ++i) {
    int len = binary_search(seq, current_best, 1, best_length, seq[i]);

    if (len == 0) {
      parent[i] = i;
    } else {
      parent[i] = current_best[len];
    }

    const int len_with_this = len + 1;

    if (len_with_this > best_length || 
        seq[i] < seq[current_best[len_with_this]]) {
      current_best[len_with_this] = i;
      best_length = max(len_with_this, best_length);
    }
  }

  return tuple<vi, int>(parent, current_best[best_length]);
}

int find_len(const vi& seq, int p) {
  return seq[p] == p ? 1 : 1 + find_len(seq, seq[p]);
}

int solve(int n, int p, int q) {
  // Rename the prince path to 1, 2, 3, 4 and so on
  // Take this naming and apply it to the princess
  // Find the longest increasing subsequence of this path,
  // the length of this path is optimal (solvable in O(N log N))

  vi prince(p+1);
  vi princess(q+1);
  for (int i = 0; i <= p; ++i) cin >> prince[i];
  for (int i = 0; i <= q; ++i) cin >> princess[i];
  vi actual_princess;
  map<int, int> renamed;
  int cnt = 0;
  for (int i : prince) renamed[i] = ++cnt;
  for (int i : princess) {
    if (renamed.find(i) != renamed.end())
      actual_princess.push_back(renamed[i]);
  }
  tuple<vi, int> solution = longest_increasing_subsequence(actual_princess);
  return find_len(get<0>(solution), get<1>(solution));
}

int main() {
  ios::sync_with_stdio(false);
  int T, n, p, q; cin >> T;
  for (int k = 1; k <= T; ++k){
    cin >> n >> p >> q;
    cout << "Case " << k << ": " << solve(n, p, q) << endl;
  }
}
