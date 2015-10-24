#include dijkstra
5 inline ValueT dist(const State& s) { return s.first + h(s.first, goal); }
where h does not overestimate distance to goal, and h is preferably monotonic
A* is polynomial if h is within O(log n) of real cost