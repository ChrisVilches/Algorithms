#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Edge = pair<int, ll>;
using Graph = vector<vector<Edge>>;
using Matrix = vector<vector<ll>>;

bool bfs(const Graph& g, const Matrix& rgraph, const int s, const int t,
         vector<int>& parent) {
  queue<int> q({s});
  fill(parent.begin(), parent.end(), -1);

  while (!q.empty()) {
    const int u = q.front();
    q.pop();

    for (const auto& [v, _] : g[u]) {
      if (parent[v] != -1 || rgraph[u][v] <= 0) continue;
      parent[v] = u;
      q.push(v);
    }
  }

  return parent[t] != -1;
}

pair<ll, Matrix> max_flow(const Graph& g, const int s, const int t) {
  Matrix rgraph(g.size(), vector<ll>(g.size(), 0));
  vector<int> parent(g.size());

  ll result = 0;

  for (int u = 0; u < (int)g.size(); u++) {
    for (const auto& [v, c] : g[u]) {
      rgraph[u][v] = max(rgraph[u][v], c);
    }
  }

  while (bfs(g, rgraph, s, t, parent)) {
    ll path_flow = LLONG_MAX;
    for (int v = t; v != s; v = parent[v]) {
      const int u = parent[v];
      path_flow = min(path_flow, rgraph[u][v]);
    }

    for (int v = t; v != s; v = parent[v]) {
      const int u = parent[v];

      rgraph[u][v] -= path_flow;
      rgraph[v][u] += path_flow;
    }

    result += path_flow;
  }

  return {result, rgraph};
}

int main() {
  int N, M, S, T;

  while (cin >> N >> M >> S >> T) {
    Graph graph(N);

    for (int i = 0; i < M; i++) {
      int u, v, c;
      cin >> u >> v >> c;
      graph[u].emplace_back(v, c);
      graph[v].emplace_back(u, 0);
    }

    const auto [_, rgraph] = max_flow(graph, S, T);

    set<int> visited{S};
    queue<int> q({S});
    while (!q.empty()) {
      const int u = q.front();
      q.pop();
      for (const auto& [v, _] : graph[u]) {
        if (!visited.count(v) && rgraph[u][v] > 0) {
          visited.emplace(v);
          q.emplace(v);
        }
      }
    }

    cout << visited.size() << endl;
    for (const int u : visited) {
      cout << u << '\n';
    }
  }
}
