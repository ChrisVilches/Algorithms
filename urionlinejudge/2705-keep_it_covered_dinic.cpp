#include <bits/stdc++.h>
using namespace std;

const int di[]{0, 0, 1, -1};
const int dj[]{1, -1, 0, 0};

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
  int R, C;
  while (cin >> R >> C) {
    vector<string> grid(R);
    for (auto& r : grid) cin >> r;

    const int node_count = (2 * R * C) + 2;
    const int s = node_count - 2;
    const int t = node_count - 1;
    Dinic g(node_count);

    long long necessary_flow = 0;

    // TODO: Study this graph a bit.

    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        const int u = (C * i) + j;
        const int cap = grid[i][j] == 'o' ? 1 : 2;
        necessary_flow += cap;

        g.add_edge(s, u, cap);

        for (int d = 0; d < 4; d++) {
          const int i2 = i + di[d];
          const int j2 = j + dj[d];
          if (i2 < 0 || j2 < 0 || i2 >= R || j2 >= C) continue;

          const int v = (C * i2) + j2;
          g.add_edge(u, R * C + v, INT_MAX);
        }

        g.add_edge(R * C + u, t, cap);
      }
    }

    cout << (g.max_flow(s, t) == necessary_flow ? 'Y' : 'N') << endl;
  }
}
