#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool hasValidPath(const vector<vector<int>>& grid) {
    const int n = grid.size();
    const int m = grid.front().size();

    queue<pair<int, int>> q;
    q.emplace(0, 0);
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    vis[0][0] = true;

    const unordered_map<int, set<pair<int, int>>> dirs = {
        {1, {{0, -1}, {0, 1}}}, {2, {{-1, 0}, {1, 0}}},  {3, {{0, -1}, {1, 0}}},
        {4, {{0, 1}, {1, 0}}},  {5, {{0, -1}, {-1, 0}}}, {6, {{0, 1}, {-1, 0}}},
    };

    while (!q.empty()) {
      const auto [i, j] = q.front();
      q.pop();

      if (i == n - 1 && j == m - 1) return true;

      for (const auto [di, dj] : dirs.at(grid[i][j])) {
        const int i2 = i + di;
        const int j2 = j + dj;
        if (i2 < 0 || j2 < 0 || i2 == n || j2 == m) continue;
        if (vis[i2][j2]) continue;
        if (!dirs.at(grid[i2][j2]).count({-di, -dj})) continue;

        vis[i2][j2] = true;
        q.emplace(i2, j2);
      }
    }

    return false;
  }
};
