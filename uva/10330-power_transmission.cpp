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

    Edge(int v, int rev, long long cap) : v(v), rev(rev), cap(cap) {}
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
  int N, M;

  while (cin >> N) {
    const int nodes = 2 * N + 2;

    Dinic g(nodes);

    for (int u = 1; u <= N; u++) {
      int c;
      cin >> c;
      g.add_edge(u, N + u, c);
    }

    cin >> M;

    for (int i = 0; i < M; i++) {
      int u, v, c;
      cin >> u >> v >> c;
      g.add_edge(N + u, v, c);
    }

    int B, D;
    cin >> B >> D;

    for (int i = 0; i < B; i++) {
      int u;
      cin >> u;
      g.add_edge(0, u, INT_MAX);
    }

    for (int i = 0; i < D; i++) {
      int u;
      cin >> u;
      g.add_edge(N + u, nodes - 1, INT_MAX);
    }

    cout << g.max_flow(0, nodes - 1) << endl;
  }
}
