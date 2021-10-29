#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef pair<double, double> pdd;

struct DisjointSets {
  int *parent, *rnk;
  int n;

  DisjointSets(int n) {
    this->n = n;
    parent = new int[n + 1];
    rnk = new int[n + 1];
    for (int i = 0; i <= n; i++) {
      rnk[i] = 0;
      parent[i] = i;
    }
  }

  int find(int u) {
    if (u != parent[u]) parent[u] = find(parent[u]);
    return parent[u];
  }

  void merge(int x, int y) {
    x = find(x), y = find(y);
    if (rnk[x] > rnk[y])
      parent[y] = x;
    else
      parent[x] = y;

    if (rnk[x] == rnk[y]) rnk[y]++;
  }
};

struct Graph {
  int V, E;
  vector<pair<double, pii>> edges;

  Graph(int V, int E) : V(V), E(E) {}

  void add_edge(int u, int v, double w) { edges.push_back({w, {u, v}}); }

  double kruskal_mst() {
    double mst_wt = 0;
    sort(edges.begin(), edges.end());

    DisjointSets ds(V);

    vector<pair<double, pii>>::iterator it;
    for (it = edges.begin(); it != edges.end(); it++) {
      int u = it->second.first;
      int v = it->second.second;

      int set_u = ds.find(u);
      int set_v = ds.find(v);

      if (set_u != set_v) {
        mst_wt += it->first;
        ds.merge(set_u, set_v);
      }
    }

    return mst_wt;
  }
};

pdd nodes[751];

double dist(pdd p, pdd q) {
  return sqrt(pow(p.first - q.first, 2) + pow(p.second - q.second, 2));
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> nodes[i].first >> nodes[i].second;
  }

  Graph g(n, n * (n - 1) / 2);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j) continue;
      g.add_edge(i, j, dist(nodes[i], nodes[j]));
    }
  }

  printf("%.6f\n", g.kruskal_mst());
}

int main() {
  int T;
  cin >> T;
  while (T--) solve();
}
