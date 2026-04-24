#include <bits/stdc++.h>
using namespace std;

struct DisjointSets {
  DisjointSets(int n) : parent(n), rank(n, 0) { iota(parent.begin(), parent.end(), 0); }

  int find(const int u) {
    if (u != parent[u]) parent[u] = find(parent[u]);
    return parent[u];
  }

  void merge(int x, int y) {
    x = find(x), y = find(y);
    if (rank[x] > rank[y])
      parent[y] = x;
    else
      parent[x] = y;

    if (rank[x] == rank[y]) rank[y]++;
  }

 private:
  vector<int> parent, rank;
};

class Solution {
 public:
  int countComponents(const vector<int>& nums, const int threshold) {
    DisjointSets ds(threshold + 1);

    for (const int x : nums) {
      for (int i = x; i <= threshold; i += x) {
        ds.merge(x, i);
      }
    }

    unordered_set<int> components;
    int extra = 0;

    for (const int x : nums) {
      if (x > threshold) {
        extra++;
      } else {
        components.emplace(ds.find(x));
      }
    }

    return extra + components.size();
  }
};
