#include <bits/stdc++.h>
using namespace std;

struct DisjointSets {
  DisjointSets(const int n) : parent(n), rank(n, 0) {
    iota(parent.begin(), parent.end(), 0);
  }

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

class SummaryRanges {
  set<int> present;
  static const int ds_size = 10'007;
  DisjointSets ds;

  optional<pair<int, int>> get(const int from) {
    const auto it = present.lower_bound(from);
    if (it == present.end()) return nullopt;

    const int first = *it;

    int lo = first + 1;
    int hi = ds_size;

    while (lo < hi) {
      const int mid = (lo + hi) / 2;
      if (ds.find(first) == ds.find(mid)) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }

    return pair<int, int>{first, lo - 1};
  }

 public:
  SummaryRanges() : ds(ds_size) {}

  void addNum(const int value) {
    if (value > 0 && present.count(value - 1)) {
      ds.merge(value - 1, value);
    }

    if (present.count(value + 1)) {
      ds.merge(value, value + 1);
    }

    present.emplace(value);
  }

  vector<vector<int>> getIntervals() {
    vector<vector<int>> res;
    int from = 0;

    while (true) {
      const optional<pair<int, int>> interval = get(from);

      if (!interval.has_value()) break;

      const auto [a, b] = interval.value();
      res.push_back({a, b});
      from = b + 1;
    }

    return res;
  }
};
