#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<vector<int>> allPathsSourceTarget(const vector<vector<int>>& graph) {
    const int n = graph.size();

    vector<vector<int>> ans;
    vector<int> curr_path;

    const function<void(int)> dfs = [&](const int u) {
      curr_path.emplace_back(u);

      if (u == n - 1) {
        ans.emplace_back(curr_path);
      } else {
        for (const int v : graph[u]) {
          dfs(v);
        }
      }

      curr_path.pop_back();
    };

    dfs(0);

    return ans;
  }
};
