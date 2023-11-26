#include <bits/stdc++.h>
using namespace std;

template <typename T>
class MinCostFlow {
  struct Edge {
    const int v;
    const T cap, cost;
    T flow;
  };
  vector<Edge> e;
  vector<vector<int>> g;

 public:
  MinCostFlow(const int n) : g(n) {}

  void add_edge(const int u, const int v, const T cap, const T cost) {
    g[u].emplace_back(e.size());
    g[v].emplace_back(e.size() + 1);
    e.push_back({v, cap, cost, 0});
    e.push_back({u, cap, -cost, cap});
  }

  pair<T, T> min_cost_flow(const T k, const int s, const int t) {
    T flow = 0;
    T cost = 0;
    const int n = g.size();

    vector<T> dist(n), pot(n);
    vector<T> f(n);
    vector<bool> vis(n);
    vector<int> parent(n);

    while (flow < k) {
      fill(dist.begin(), dist.end(), numeric_limits<T>::max());
      fill(vis.begin(), vis.end(), false);
      dist[s] = 0;
      f[s] = k - flow;

      priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> q;
      q.emplace(0, s);
      while (!q.empty()) {
        const auto [d, u] = q.top();
        q.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (const int i : g[u]) {
          const auto [v, cap, cost, flow] = e[i];
          const T d2 = d + cost + pot[u] - pot[v];
          if (!vis[v] && flow < cap && d2 < dist[v]) {
            dist[v] = d2;
            f[v] = min(f[u], cap - flow);
            parent[v] = i;
            q.emplace(d2, v);
          }
        }
      }

      if (!vis[t]) break;

      for (int i = 0; i < n; i++) {
        if (dist[i] != numeric_limits<T>::max()) {
          dist[i] += pot[i];
        }
      }

      cost += dist[t] * f[t];
      flow += f[t];

      for (int u = t; u != s; u = e[parent[u] ^ 1].v) {
        e[parent[u]].flow += f[t];
        e[parent[u] ^ 1].flow -= f[t];
      }

      dist.swap(pot);
    }
    return {flow, cost};
  }
};

int main() {
  int n, k;
  while (cin >> n >> k) {
    const int nodes = 2 * n + 3;
    const int sink = nodes - 1;

    MinCostFlow<int> g(nodes);

    g.add_edge(0, 1, k, 0);

    for (int i = 0; i < n; i++) {
      g.add_edge(0, 2 + i, 1, 0);
      g.add_edge(2 + n + i, sink, 1, 0);
    }

    for (int i = 0; i < n; i++) {
      for (int j = i; j < n; j++) {
        int cost;
        cin >> cost;
        g.add_edge(1 + i, 2 + n + j, 1, cost);
      }
    }

    cout << g.min_cost_flow(n, 0, sink).second << endl;
  }
}
