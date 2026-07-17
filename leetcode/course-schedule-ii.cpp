#include <bits/stdc++.h>
using namespace std;

class Solution {
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

 public:
  vector<int> findOrder(const int numCourses, const vector<vector<int>>& prerequisites) {
    const int n = numCourses;

    vector<vector<int>> graph(n);

    for (const auto& edge : prerequisites) {
      const int u = edge.front();
      const int v = edge.back();
      graph[u].emplace_back(v);
    }

    if (has_cycle(graph)) return {};

    vector<bool> visited(n, false);
    vector<int> ans;

    const function<void(int)> dfs = [&](const int u) {
      if (visited[u]) return;
      visited[u] = true;
      for (const int v : graph[u]) {
        dfs(v);
      }
      ans.emplace_back(u);
    };

    for (int i = 0; i < n; i++) {
      if (visited[i]) continue;
      dfs(i);
    }

    return ans;
  }
};
