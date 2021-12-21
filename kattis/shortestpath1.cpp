#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pii;

const int INF = 10e8;

// Simple Dijkstra.

int nodes, edges, init_node, queries;
int dist[10000];

void dijkstra(map<int, vector<pair<int, int>>>& graph) {
  fill(dist, dist + nodes, INF);

  priority_queue<pii, vector<pii>, greater<pii>> q;

  q.push({0, init_node});
  dist[init_node] = 0;

  while (!q.empty()) {
    auto [_, u] = q.top();
    q.pop();
    for (auto& [v, weight] : graph[u]) {
      int alt = dist[u] + weight;
      if (alt < dist[v]) {
        dist[v] = alt;
        q.push({alt, v});
      }
    }
  }
}

void solve() {
  int query;
  map<int, vector<pair<int, int>>> graph;

  for (int i = 0; i < edges; i++) {
    int u, v, w;
    cin >> u >> v >> w;

    graph[u].push_back({v, w});
  }

  dijkstra(graph);

  for (int i = 0; i < queries; i++) {
    cin >> query;
    if (dist[query] == INF) {
      cout << "Impossible" << endl;
    } else {
      cout << dist[query] << endl;
    }
  }
}

int main() {
  while (scanf("%d %d %d %d", &nodes, &edges, &queries, &init_node) == 4) {
    if (nodes == 0 && edges == 0 && init_node == 0 && queries == 0) return 0;
    solve();
  }
}
