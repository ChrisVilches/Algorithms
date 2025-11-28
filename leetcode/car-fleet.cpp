#include <bits/stdc++.h>
using namespace std;

struct DisjointSets {
  DisjointSets(const int n) : parent(vector<int>(n)) {
    iota(parent.begin(), parent.end(), 0);
  }

  int find(const int u) {
    if (u != parent[u]) parent[u] = find(parent[u]);
    return parent[u];
  }

  void merge(const int x, const int y) { parent[find(x)] = find(y); }

 private:
  vector<int> parent;
};

class Solution {
 public:
  int carFleet(const int target, const vector<int>& position, const vector<int>& speed) {
    const int n = position.size();
    vector<pair<int, int>> cars;

    for (int i = 0; i < n; i++) cars.emplace_back(position[i], speed[i]);
    sort(cars.begin(), cars.end());

    priority_queue<pair<double, int>> pq;
    DisjointSets ds(n);

    for (int i = 0; i < n; i++) {
      const auto [pos, v] = cars[i];
      const double time = static_cast<double>(target - pos) / v;

      while (!pq.empty()) {
        const auto [t, idx] = pq.top();
        if (-t > time) break;
        ds.merge(idx, i);
        pq.pop();
      }

      pq.emplace(-time, i);
    }

    unordered_set<int> sets;
    for (int i = 0; i < n; i++) sets.emplace(ds.find(i));
    return sets.size();
  }
};
