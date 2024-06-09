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

int main() {
  int n, e, p;
  while (cin >> n >> e >> p) {
    vector<pair<double, double>> points(n);
    for (auto& p : points) cin >> p.first >> p.second;

    DisjointSets ds(n);

    for (int i = 0; i < p; i++) {
      int a, b;
      cin >> a >> b;
      ds.merge(a - 1, b - 1);
    }

    vector<tuple<double, int, int>> edges;

    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        const double dx = points[i].first - points[j].first;
        const double dy = points[i].second - points[j].second;
        edges.emplace_back(hypot(dx, dy), i, j);
      }
    }

    sort(edges.begin(), edges.end());

    double ans = 0;

    const auto ok = [&](const int u) {
      for (int v = 0; v < e; v++) {
        if (ds.find(v) == ds.find(u)) return true;
      }
      return false;
    };

    for (const auto& [w, u, v] : edges) {
      if (ds.find(u) == ds.find(v)) continue;
      if (ok(u) && ok(v)) continue;

      ds.merge(u, v);
      ans += w;
    }

    cout << fixed << setprecision(9) << ans << endl;
  }
}
