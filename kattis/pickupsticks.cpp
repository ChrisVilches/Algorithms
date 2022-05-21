#include <bits/stdc++.h>
using namespace std;

vector<int> toposort(const vector<vector<int>>& graph) {
  vector<bool> visited(graph.size(), false);
  stack<pair<int, int>> dfs;
  vector<int> order;
  for (int i = 0; i < (int)graph.size(); i++) {
    if (!visited[i]) dfs.push({false, i});

    while (!dfs.empty()) {
      const auto [parent, u] = dfs.top();
      dfs.pop();

      if (parent) {
        order.push_back(u);
        continue;
      }

      if (visited[u]) continue;
      visited[u] = true;
      dfs.push({true, u});

      for (const int v : graph[u])
        if (!visited[v]) dfs.push({false, v});
    }
  }
  reverse(order.begin(), order.end());
  return order;
}

bool has_cycle(const vector<vector<int>>& graph) {
  vector<bool> visited(graph.size(), false);
  vector<bool> path(graph.size(), false);

  function<bool(int)> dfs = [&](const int u) {
    if (!visited[u]) {
      visited[u] = true;
      path[u] = true;
      for (const int v : graph[u]) {
        if (!visited[v] && dfs(v))
          return true;
        else if (path[v])
          return true;
      }
    }

    path[u] = false;
    return false;
  };

  for (int i = 0; i < (int)graph.size(); i++)
    if (!visited[i] && dfs(i)) return true;

  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M;

  while (cin >> N >> M && N > 0) {
    vector<set<int>> graph_unique(N);

    while (M--) {
      int u, v;
      cin >> u >> v;

      graph_unique[u - 1].insert(v - 1);
    }

    vector<vector<int>> graph(N);

    for (int i = 0; i < N; i++)
      graph[i] = vector<int>(graph_unique[i].begin(), graph_unique[i].end());

    if (has_cycle(graph)) {
      cout << "IMPOSSIBLE" << endl;
    } else {
      for (const int u : toposort(graph)) {
        cout << u + 1 << endl;
      }
    }
  }
}
