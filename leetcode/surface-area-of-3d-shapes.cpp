#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int surfaceArea(const vector<vector<int>>& grid) {
    const int n = grid.size();
    const int m = grid.front().size();

    int ans = 0;

    for (const auto& row : grid) {
      for (const int x : row) {
        if (x > 0) ans += 2;
      }
    }

    for (int i = 0; i < n; i++) {
      ans += grid[i][0];
      ans += grid[i][m - 1];
    }

    for (int j = 0; j < m; j++) {
      ans += grid[0][j];
      ans += grid[n - 1][j];
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        const int h = grid[i][j];

        if (j > 0) ans += max(0, h - grid[i][j - 1]);
        if (j < m - 1) ans += max(0, h - grid[i][j + 1]);
        if (i > 0) ans += max(0, h - grid[i - 1][j]);
        if (i < n - 1) ans += max(0, h - grid[i + 1][j]);
      }
    }

    return ans;
  }
};
