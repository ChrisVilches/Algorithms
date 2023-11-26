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

bool is_weekend(const int day) {
  const int d = (day - 1) % 7;
  return d == 5 || d == 6;
}

tuple<int, int, Dinic> build_graph(const vector<pair<int, int>>& intervals,
                                   const int pairs, const bool include_weekends) {
  const int n = 1 + 100 + intervals.size() + 1;
  Dinic dinic(n);

  for (int i = 1; i <= 100; i++) {
    dinic.add_edge(0, i, pairs);
  }

  for (int i = 0; i < (int)intervals.size(); i++) {
    const auto [b, e] = intervals[i];
    const int piano_idx = 1 + 100 + i;
    for (int i = b; i <= e; i++) {
      if (is_weekend(i) && !include_weekends) continue;
      dinic.add_edge(i, piano_idx, 1);
    }
    dinic.add_edge(piano_idx, n - 1, 1);
  }

  return {0, n - 1, dinic};
}

void solve() {
  int pianos, tuners;
  cin >> pianos >> tuners;

  vector<pair<int, int>> intervals(pianos);
  for (auto& [b, e] : intervals) cin >> b >> e;

  for (int i = 0; i < 2; i++) {
    auto [source, sink, graph] = build_graph(intervals, tuners / 2, i == 1);

    if (graph.max_flow(source, sink) == pianos) {
      cout << (i == 0 ? "fine" : "weekend work") << endl;
      return;
    }
  }

  cout << "serious trouble" << endl;
}

int main() {
  int t;
  cin >> t;
  while (t--) solve();
}
