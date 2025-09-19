#include <bits/stdc++.h>
using namespace std;

class Solution {
  const array<int, 4> di{-1, 1, 0, 0}, dj{0, 0, -1, 1};

 public:
  int shortestBridge(vector<vector<int>>& grid) {
    const int n = grid.size();
    const int m = grid.front().size();

    queue<tuple<int, int, int>> q;

    const function<void(int, int)> dfs = [&](const int i, const int j) {
      if (i < 0 || j < 0 || i == n || j == m) return;
      if (grid[i][j] != 1) return;
      q.emplace(i, j, 0);

      grid[i][j] = 2;
      for (int d = 0; d < 4; d++) {
        dfs(i + di[d], j + dj[d]);
      }
    };

    for (int i = 0; i < n && q.empty(); i++) {
      for (int j = 0; j < m && q.empty(); j++) {
        if (grid[i][j] == 1) dfs(i, j);
      }
    }

    while (!q.empty()) {
      const auto [i, j, dist] = q.front();
      q.pop();

      for (int d = 0; d < 4; d++) {
        const int i2 = i + di[d];
        const int j2 = j + dj[d];
        if (i2 < 0 || j2 < 0 || i2 == n || j2 == m || grid[i2][j2] == 2) continue;
        if (grid[i2][j2] == 1) return dist;

        q.emplace(i2, j2, dist + 1);
        grid[i2][j2] = 2;
      }
    }

    assert(false);
  }
};
