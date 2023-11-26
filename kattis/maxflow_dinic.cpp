#include <bits/stdc++.h>
using namespace std;

struct Dinic {
  Dinic(const int n) : graph(n), level(n), ptr(n) {}

  long long max_flow(const int s, const int t) {
    long long f = 0;
    while (bfs(s, t)) {
      fill(ptr.begin(), ptr.end(), 0);
      while (const long long df = dfs(s, t, 1e18)) f += df;
    }
    return f;
  }

  void add_edge(const int u, const int v, const long long cap) {
    const int r1 = graph[v].size();
    const int r2 = graph[u].size();
    graph[u].push_back({v, r1, cap});
    graph[v].push_back({u, r2, 0});
  }

  vector<tuple<int, int, long long>> flow_edges() const {
    vector<tuple<int, int, long long>> res;
    for (int u = 0; u < (int)graph.size(); u++) {
      for (const Edge edge : graph[u]) {
        if (edge.flow > 0) {
          res.emplace_back(u, edge.v, edge.flow);
        }
      }
    }
    return res;
  }

 private:
  struct Edge {
    const int v, rev;
    const long long cap;
    long long flow = 0;
  };

  vector<vector<Edge>> graph;
  vector<int> level, ptr;

  bool bfs(const int s, const int t) {
    fill(level.begin(), level.end(), -1);
    queue<int> q({s});
    level[s] = 0;
    while (!q.empty()) {
      const int u = q.front();
      q.pop();
      for (const Edge edge : graph[u]) {
        if (level[edge.v] != -1 || edge.cap <= edge.flow) continue;
        level[edge.v] = level[u] + 1;
        q.push(edge.v);
      }
    }
    return level[t] != -1;
  }

  long long dfs(const int u, const int t, const long long flow) {
    if (u == t) return flow;
    for (int& i = ptr[u]; i < (int)graph[u].size(); i++) {
      Edge& edge = graph[u][i];
      if (level[u] + 1 != level[edge.v] || edge.cap <= edge.flow) continue;
      const long long f = dfs(edge.v, t, min(flow, edge.cap - edge.flow));
      if (f == 0) continue;
      edge.flow += f;
      graph[edge.v][edge.rev].flow -= f;
      return f;
    }
    return 0;
  }
};

int main() {
  int n, m, s, t;

  while (cin >> n >> m >> s >> t) {
    Dinic dinic(n);
    while (m--) {
      int u, v, c;
      cin >> u >> v >> c;
      dinic.add_edge(u, v, c);
    }

    const long long flow = dinic.max_flow(s, t);
    const auto edges = dinic.flow_edges();

    cout << n << " " << flow << " " << edges.size() << endl;

    for (const auto& [u, v, f] : edges) {
      cout << u << " " << v << " " << f << endl;
    }
  }
}
