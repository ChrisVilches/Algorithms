#include <bits/stdc++.h>
using namespace std;

class Solution {
  int count(const vector<vector<int>>& graph, const int src, const int k) {
    vector<bool> visited(graph.size(), false);
    queue<pair<int, int>> q;
    q.emplace(src, 0);
    visited[src] = true;

    int res = 0;

    while (!q.empty()) {
      const auto [u, dist] = q.front();
      q.pop();
      if (dist > k) continue;
      res++;
      for (const int v : graph[u]) {
        if (visited[v]) continue;
        visited[v] = true;
        q.emplace(v, dist + 1);
      }
    }

    return res;
  }

  vector<vector<int>> make_graph(const vector<vector<int>>& edges) {
    vector<vector<int>> res(edges.size() + 1);

    for (const auto& edge : edges) {
      const int u = edge.front();
      const int v = edge.back();
      res[u].emplace_back(v);
      res[v].emplace_back(u);
    }

    return res;
  }

 public:
  vector<int> maxTargetNodes(const vector<vector<int>>& edges1,
                             const vector<vector<int>>& edges2, const int k) {
    const vector<vector<int>> A = make_graph(edges1);
    const vector<vector<int>> B = make_graph(edges2);

    int best_count = 0;

    for (size_t i = 0; i < B.size(); i++) {
      best_count = max(best_count, count(B, i, k - 1));
    }

    vector<int> ans;

    for (size_t i = 0; i < A.size(); i++) {
      ans.emplace_back(count(A, i, k) + best_count);
    }

    return ans;
  }
};
