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

int main() {
  int n, q, s;
  while (cin >> n >> q >> s) {
    vector<int> sensor_queue(s);
    vector<int> queue_size(q);
    int total_data = 0;

    for (int i = 0; i < s; i++) {
      int qi;
      cin >> qi;
      sensor_queue[i] = qi - 1;
    }

    for (auto& q : queue_size) {
      cin >> q;
    }

    vector<pair<int, vector<int>>> windows(n);

    for (auto& [d, queue_data] : windows) {
      cin >> d;
      queue_data.assign(q, 0);
      for (int i = 0; i < s; i++) {
        int a;
        cin >> a;
        total_data += a;
        auto& d = queue_data[sensor_queue[i]];
        d = min(d + a, queue_size[sensor_queue[i]]);
      }
    }

    const int nodes_per_window = 2 + q;
    const int graph_size = 2 + (nodes_per_window * n);

    Dinic dinic(graph_size);

    for (int w = 0; w < n; w++) {
      const int offset = 1 + nodes_per_window * w;

      dinic.add_edge(0, offset, INT_MAX);

      const auto [d, queue_data] = windows[w];

      for (int i = 0; i < q; i++) {
        const int q_node = offset + 1 + i;
        dinic.add_edge(offset, q_node, queue_data[i]);
        dinic.add_edge(q_node, offset + q + 1, queue_size[i]);

        if (w < n - 1) {
          const int next_offset = 1 + nodes_per_window * (w + 1);
          const int cap = queue_size[i] - windows[w + 1].second[i];
          dinic.add_edge(q_node, next_offset + 1 + i, cap);
        }
      }

      dinic.add_edge(offset + q + 1, graph_size - 1, d);
    }

    const long long flow = dinic.max_flow(0, graph_size - 1);
    cout << (total_data == flow ? "possible" : "impossible") << endl;
  }
}
