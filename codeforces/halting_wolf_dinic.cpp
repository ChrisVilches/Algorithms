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

Dinic read_network_graph(const int N) {
  const int sink = N;
  Dinic graph(N + 1);

  string in;
  int n, v;

  auto transform_v = [sink](int& v) -> void {
    v--;
    if (v == 0) v = sink;
  };

  for (int u = 0; u < N; u++) {
    cin >> in;

    if (in[0] == '*') {
      cin >> v;
      transform_v(v);
      graph.add_edge(u, v, LONG_LONG_MAX);
    } else {
      stringstream ss(in);
      ss >> n;
      map<int, int> edges;

      while (n--) {
        cin >> v;
        transform_v(v);
        edges[v]++;
      }

      for (auto const [v, c] : edges) {
        graph.add_edge(u, v, c);
      }
    }
  }

  return graph;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

  while (cin >> N) {
    const long long flow = read_network_graph(N).max_flow(0, N);

    if (flow == LONG_LONG_MAX) {
      cout << "*" << endl;
    } else {
      cout << flow + 1 << endl;
    }
  }
}
