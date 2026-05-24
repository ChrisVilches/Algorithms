#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool validateBinaryTreeNodes(const int n, const vector<int>& left,
                               const vector<int>& right) {
    vector<vector<int>> graph(n);
    vector<int> in_deg(n, 0);

    for (int u = 0; u < n; u++) {
      if (left[u] != -1) {
        in_deg[left[u]]++;
        graph[u].emplace_back(left[u]);
        graph[left[u]].emplace_back(u);
      }

      if (right[u] != -1) {
        in_deg[right[u]]++;
        graph[u].emplace_back(right[u]);
        graph[right[u]].emplace_back(u);
      }
    }

    int in_deg0_count = 0;
    for (const int x : in_deg) {
      if (x == 0) in_deg0_count++;
      if (x > 1) return false;
    }

    if (in_deg0_count != 1) return false;

    vector<bool> vis(n, false);

    const function<void(int)> dfs = [&](const int u) {
      if (vis[u]) return;
      vis[u] = true;

      for (const int v : graph[u]) {
        dfs(v);
      }
    };

    dfs(0);

    return accumulate(vis.begin(), vis.end(), 0) == n;
  }
};
