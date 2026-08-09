#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<vector<int>> graph;

  void dfs_aux(const int u, const int dist, vector<int>& out) {
    if (out[u] != -1) return;
    out[u] = dist;
    for (const int v : graph[u]) {
      dfs_aux(v, dist + 1, out);
    }
  }

  vector<int> dfs(const int u) {
    vector<int> res(graph.size(), -1);
    dfs_aux(u, 0, res);
    return res;
  }

 public:
  vector<int> findMinHeightTrees(const int n, const vector<vector<int>>& edges) {
    graph.resize(n);

    for (const auto& edge : edges) {
      const int u = edge.front();
      const int v = edge.back();
      graph[u].emplace_back(v);
      graph[v].emplace_back(u);
    }

    const vector<int> dist = dfs(0);

    const int a = distance(dist.begin(), max_element(dist.begin(), dist.end()));

    const vector<int> dist_a = dfs(a);

    const int b = distance(dist_a.begin(), max_element(dist_a.begin(), dist_a.end()));

    const vector<int> dist_b = dfs(b);

    int min_val = INT_MAX;
    for (int u = 0; u < n; u++) {
      min_val = min(min_val, max(dist_a[u], dist_b[u]));
    }

    vector<int> ans;

    for (int u = 0; u < n; u++) {
      if (max(dist_a[u], dist_b[u]) == min_val) ans.emplace_back(u);
    }

    return ans;
  }
};
