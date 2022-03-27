#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pii;
const int INF = 1e8;

vector<int> dijkstra(const vector<vector<pii>>& graph, const int source) {
  vector<int> dist(graph.size(), INF);

  priority_queue<pii, vector<pii>, greater<pii>> q;

  q.push({0, source});
  dist[source] = 0;

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

  return dist;
}

void solve(const int N, const int M, const int C, const int K) {
  vector<map<int, int>> graph_only_service(N);
  vector<vector<pii>> graph_without_service(N);

  for (int i = 0; i < M; i++) {
    int u, v, w;
    cin >> u >> v >> w;

    if (u < C && v < C) {
      graph_only_service[u][v] = w;
      graph_only_service[v][u] = w;
    } else {
      if (u >= C) graph_without_service[u].push_back({v, w});
      if (v >= C) graph_without_service[v].push_back({u, w});
    }
  }

  vector<int> psum(C);

  psum[0] = 0;

  for (int i = 1; i < C; i++) {
    psum[i] = psum[i - 1] + graph_only_service[i - 1][i];
  }

  vector<int> paths_from_repair_city = dijkstra(graph_without_service, K);

  auto range_sum = [&](const int l, const int r) {
    if (l == r) return 0;
    if (l == 0) return psum[r];
    return psum[r] - psum[l];
  };

  int ans = INT_MAX;

  for (int i = 0; i < C; i++) {
    int path = paths_from_repair_city[i] + range_sum(i, C - 1);
    ans = min(ans, path);
  }

  cout << ans << endl;
}

int main() {
  int N, M, C, K;

  while (cin >> N >> M >> C >> K && N && M && C && K) solve(N, M, C, K);
}
