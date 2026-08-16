#include <bits/stdc++.h>
using namespace std;

class Solution {
  bool has_cycle(const vector<vector<int>>& graph) {
    vector<bool> visited(67, false);
    vector<bool> path(67, false);

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

    for (size_t i = 0; i < graph.size(); i++)
      if (!visited[i] && dfs(i)) return true;

    return false;
  }

 public:
  bool isPrintable(vector<vector<int>>& targetGrid) {
    vector<vector<int>> graph(67);

    const int n = targetGrid.size();
    const int m = targetGrid.front().size();

    for (int color = 0; color < static_cast<int>(graph.size()); color++) {
      int min_x = 100;
      int min_y = 100;
      int max_x = 0;
      int max_y = 0;

      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          if (targetGrid[i][j] != color) continue;

          min_x = min(min_x, j);
          min_y = min(min_y, i);
          max_x = max(max_x, j);
          max_y = max(max_y, i);
        }
      }

      set<int> edges;

      for (int i = min_y; i <= max_y; i++) {
        for (int j = min_x; j <= max_x; j++) {
          if (targetGrid[i][j] != color) edges.emplace(targetGrid[i][j]);
        }
      }

      graph[color] = {edges.begin(), edges.end()};
    }

    return !has_cycle(graph);
  }
};
