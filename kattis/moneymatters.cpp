#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> nums(n);
  for (auto& x : nums) cin >> x;

  vector<vector<int>> graph(n);

  while (m--) {
    int u, v;
    cin >> u >> v;
    graph[u].emplace_back(v);
    graph[v].emplace_back(u);
  }

  vector<bool> visited(n, false);

  for (int u = 0; u < n; u++) {
    if (visited[u]) continue;
    int total = 0;

    const function<void(int)> dfs = [&](const int u) {
      if (visited[u]) return;
      visited[u] = true;
      total += nums[u];
      for (const int v : graph[u]) dfs(v);
    };

    dfs(u);

    if (total != 0) {
      cout << "IMPOSSIBLE" << endl;
      return 0;
    }
  }

  cout << "POSSIBLE" << endl;
}
