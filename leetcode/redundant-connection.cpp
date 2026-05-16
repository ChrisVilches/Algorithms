#include <bits/stdc++.h>
using namespace std;

struct DisjointSets {
  DisjointSets(const int n) : parent(n) { clear(); }

  int find(const int u) {
    if (u != parent[u]) parent[u] = find(parent[u]);
    return parent[u];
  }

  void merge(const int x, const int y) { parent[find(x)] = find(y); }
  void clear() { iota(parent.begin(), parent.end(), 0); }

 private:
  vector<int> parent;
};

class Solution {
 public:
  vector<int> findRedundantConnection(const vector<vector<int>>& edges) {
    int n = 0;

    for (const vector<int>& edge : edges) {
      n = max(n, edge.front());
      n = max(n, edge.back());
    }

    n++;

    DisjointSets ds(n);

    for (const vector<int>& candidate : views::reverse(edges)) {
      ds.clear();

      for (const vector<int>& edge : edges) {
        if (edge == candidate) continue;

        ds.merge(edge.front(), edge.back());
      }

      if (ds.find(candidate.front()) == ds.find(candidate.back())) {
        return candidate;
      }
    }

    assert(false);
  }
};
