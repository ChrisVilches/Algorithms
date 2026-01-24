#include <bits/stdc++.h>
using namespace std;
using Graph = vector<vector<int>>;

vector<int> kosaraju(const Graph& out_graph, const Graph& in_graph) {
  const int n = out_graph.size();
  stack<int> s;

  vector<bool> visited(n, false);

  const function<void(int)> dfs_post_order = [&](const int u) {
    if (visited[u]) return;
    visited[u] = true;
    for (const int v : out_graph[u]) dfs_post_order(v);
    s.push(u);
  };

  for (int u = 0; u < n; u++) {
    if (!visited[u]) dfs_post_order(u);
  }

  vector<int> assign(n, -1);

  const function<void(int, int)> dfs_assign = [&](const int u, const int root) {
    if (assign[u] != -1) return;
    assign[u] = root;
    for (const int v : in_graph[u]) dfs_assign(v, root);
  };

  while (!s.empty()) {
    const int u = s.top();
    s.pop();
    if (assign[u] == -1) dfs_assign(u, u);
  }

  return assign;
}

void solve() {
  int n, m;
  cin >> n >> m;
  Graph out_graph(n), in_graph(n);

  while (m--) {
    int u, v;
    cin >> u >> v;
    out_graph[u - 1].emplace_back(v - 1);
    in_graph[v - 1].emplace_back(u - 1);
  }

  const vector<int> assignment = kosaraju(out_graph, in_graph);
  map<int, set<int>> assignment_map;

  for (int i = 0; i < n; i++) {
    const int component = assignment[i];
    assignment_map[component].emplace(i);
  }

  int ans = 0;

  for (const auto& [component, nodes] : assignment_map) {
    bool has = false;
    for (const int u : nodes) {
      for (const int in : in_graph[u]) {
        if (assignment[in] != component) has = true;
      }
    }

    if (!has) ans++;
  }

  cout << ans << endl;
}

int main() {
  int t;
  cin >> t;
  while (t--) solve();
}
