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

void solve() {
  int N, M;
  cin >> N >> M;

  map<string, int> size_node;
  size_node["XXL"] = 1;
  size_node["XL"] = 2;
  size_node["L"] = 3;
  size_node["M"] = 4;
  size_node["S"] = 5;
  size_node["XS"] = 6;

  const int volunteer_offset = 7;
  const int target = volunteer_offset + M;
  const int nodes = 1 + size_node.size() + M + 1;

  Dinic dinic(nodes);

  for (const auto& [_, i] : size_node) {
    dinic.add_edge(0, i, N / 6);
  }

  for (int i = 0; i < M; i++) {
    string s1, s2;
    cin >> s1 >> s2;
    const int volunteer_node = volunteer_offset + i;
    dinic.add_edge(size_node[s1], volunteer_node, 1);
    dinic.add_edge(size_node[s2], volunteer_node, 1);
    dinic.add_edge(volunteer_node, target, 1);
  }

  cout << (dinic.max_flow(0, target) == M ? "YES" : "NO") << endl;
}

int main() {
  int T;
  cin >> T;
  while (T--) solve();
}
