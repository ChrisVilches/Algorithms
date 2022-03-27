#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pii;
const int INF = 10e8;

int dijkstra(const vector<vector<pii>>& graph, const int s, const int t) {
  vector<int> dist(graph.size(), INF);

  priority_queue<pii, vector<pii>, greater<pii>> q;

  q.push({0, s});
  dist[s] = 0;

  while (!q.empty()) {
    auto [_, u] = q.top();
    q.pop();
    for (const auto& [v, weight] : graph[u]) {
      int alt = dist[u] + weight;
      if (alt < dist[v]) {
        dist[v] = alt;
        q.push({alt, v});
      }
    }
  }

  return dist[t];
}

int main() {
  int T;
  cin >> T;

  for (int test = 0; test < T; test++) {
    int n, m, s, t;
    cin >> n >> m >> s >> t;

    vector<vector<pii>> graph(n);

    for (int i = 0; i < m; i++) {
      int u, v, w;
      cin >> u >> v >> w;

      graph[u].push_back({v, w});
      graph[v].push_back({u, w});
    }

    cout << "Case #" << test + 1 << ": ";
    int path = dijkstra(graph, s, t);

    if (path == INF) {
      cout << "unreachable" << endl;
    } else {
      cout << path << endl;
    }
  }
}
