#include <bits/stdc++.h>
using namespace std;

class Solution {
  const array<int, 4> di{0, 0, -1, 1};
  const array<int, 4> dj{-1, 1, 0, 0};

 public:
  int minimumEffortPath(const vector<vector<int>>& grid) {
    const auto bfs = [&](const int max_cost) {
      const int n = grid.size();
      const int m = grid.front().size();
      vector<vector<bool>> vis(n, vector<bool>(m, false));
      vis[0][0] = true;
      queue<pair<int, int>> q;
      q.emplace(0, 0);

      while (!q.empty()) {
        const auto [i, j] = q.front();
        q.pop();
        if (i == n - 1 && j == m - 1) return true;

        for (int d = 0; d < 4; d++) {
          const int i2 = i + di[d];
          const int j2 = j + dj[d];

          if (i2 < 0 || j2 < 0 || i2 >= n || j2 >= m) continue;
          if (vis[i2][j2]) continue;
          if (abs(grid[i][j] - grid[i2][j2]) > max_cost) continue;
          vis[i2][j2] = true;
          q.emplace(i2, j2);
        }
      }

      return false;
    };

    int lo = 0;
    int hi = 1e6 + 7;

    while (lo < hi) {
      const int mid = (lo + hi) / 2;

      if (bfs(mid)) {
        hi = mid;
      } else {
        lo = mid + 1;
      }
    }

    return lo;
  }
};
