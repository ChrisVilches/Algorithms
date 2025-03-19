#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<set<int>> to_graph(const int n, const vector<vector<int>>& edges) {
    vector<set<int>> graph(n);
    for (const auto& edge : edges) {
      graph[edge.front()].emplace(edge.back());
      graph[edge.back()].emplace(edge.front());
    }

    return graph;
  }

 public:
  int minTime(const int n, const vector<vector<int>>& edges,
              const vector<bool>& hasApple) {
    const vector<set<int>> graph = to_graph(n, edges);

    vector<bool> visited(n, false);

    const function<int(int)> dfs = [&](const int u) {
      visited[u] = true;
      int res = 0;

      for (const int v : graph[u]) {
        if (visited[v]) continue;

        res += dfs(v);
      }

      const int node_visited = res > 0 || hasApple[u];

      return res + (node_visited ? 2 : 0);
    };

    return max(dfs(0) - 2, 0);
  }
};
