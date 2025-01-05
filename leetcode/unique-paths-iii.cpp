#include <bits/stdc++.h>
using namespace std;

class Solution {
  const int di[4]{-1, 1, 0, 0};
  const int dj[4]{0, 0, -1, 1};

 public:
  int uniquePathsIII(const vector<vector<int>>& grid) {
    queue<vector<pair<int, int>>> q;

    const int n = grid.size();
    const int m = grid.front().size();

    pair<int, int> src, target;
    int empty_count = 0;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (grid[i][j] == 1) src = {i, j};
        if (grid[i][j] == 2) target = {i, j};
        if (grid[i][j] == 0) empty_count++;
      }
    }

    int ans = 0;
    set<pair<int, int>> path;
    int path_empty = 0;

    function<void(int, int)> dfs = [&](const int i, const int j) {
      if (i < 0 || j < 0 || i >= n || j >= m) return;
      if (grid[i][j] == -1) return;
      if (path.count({i, j})) return;
      if (i == target.first && j == target.second) {
        ans += path_empty == empty_count;
        return;
      }

      path.emplace(i, j);
      path_empty += grid[i][j] == 0;

      for (int d = 0; d < 4; d++) {
        dfs(i + di[d], j + dj[d]);
      }

      path_empty -= grid[i][j] == 0;
      path.erase({i, j});
    };

    dfs(src.first, src.second);

    return ans;
  }
};
