#include <bits/stdc++.h>
using namespace std;

struct FlowEdge {
  int u, v;
  long long cap, flow = 0;
  FlowEdge(int u, int v, long long cap) : u(u), v(v), cap(cap) {}
};

struct Dinic {
  vector<FlowEdge> edges;

  Dinic(const int n, const int s, const int t) : n(n), s(s), t(t) {
    adj.resize(n);
    level.resize(n);
    ptr.resize(n);
  }

  long long flow() {
    long long f = 0;
    while (true) {
      fill(level.begin(), level.end(), -1);
      level[s] = 0;
      if (!bfs()) break;
      fill(ptr.begin(), ptr.end(), 0);
      while (long long pushed = dfs(s, flow_inf)) {
        f += pushed;
      }
    }
    return f;
  }

  void add_edge(const int u, const int v, const long long cap) {
    edges.emplace_back(u, v, cap);
    edges.emplace_back(v, u, 0);
    adj[u].push_back(m++);
    adj[v].push_back(m++);
  }

 private:
  const long long flow_inf = 1e18;
  vector<vector<int>> adj;
  int n, m = 0;
  int s, t;
  vector<int> level, ptr;
  queue<int> q;

  bool bfs() {
    q.push(s);
    while (!q.empty()) {
      const int u = q.front();
      q.pop();
      for (const int id : adj[u]) {
        const FlowEdge edge = edges[id];
        if (edge.cap - edge.flow < 1) continue;
        if (level[edge.v] != -1) continue;
        level[edge.v] = level[u] + 1;
        q.push(edge.v);
      }
    }
    return level[t] != -1;
  }

  long long dfs(const int u, const long long pushed) {
    if (pushed == 0) return 0;
    if (u == t) return pushed;
    for (int& cid = ptr[u]; cid < (int)adj[u].size(); cid++) {
      const int id = adj[u][cid];
      const int v = edges[id].v;
      if (level[u] + 1 != level[v] || edges[id].cap - edges[id].flow < 1) continue;
      const long long tr = dfs(v, min(pushed, edges[id].cap - edges[id].flow));
      if (tr == 0) continue;
      edges[id].flow += tr;
      edges[id ^ 1].flow -= tr;
      return tr;
    }
    return 0;
  }
};

int main() {
  int n, m, s, t;

  while (cin >> n >> m >> s >> t) {
    Dinic dinic(n, s, t);
    while (m--) {
      int u, v, c;
      cin >> u >> v >> c;
      dinic.add_edge(u, v, c);
    }

    const long long flow = dinic.flow();

    vector<tuple<int, int, long long>> edges;
    for (const FlowEdge edge : dinic.edges) {
      if (edge.flow > 0) {
        edges.emplace_back(edge.u, edge.v, edge.flow);
      }
    }

    sort(edges.begin(), edges.end());

    cout << n << " " << flow << " " << edges.size() << endl;

    for (const auto& [u, v, f] : edges) {
      cout << u << " " << v << " " << f << endl;
    }
  }
}
