#include <bits/stdc++.h>
using namespace std;

class Solution {
  const int di[4] = {-1, 1, 0, 0};
  const int dj[4] = {0, 0, -1, 1};
  int n, m;
  vector<vector<int>> grid;
  int dfs(const int i, const int j) {
    if (i < 0 || j < 0 || i >= n || j >= m) return 0;
    if (grid[i][j] != 1) return 0;
    grid[i][j] = -1;

    int total = 1;
    for (int d = 0; d < 4; d++) {
      total += dfs(i + di[d], j + dj[d]);
    }
    return total;
  }

 public:
  int maxAreaOfIsland(vector<vector<int>>& grid) {
    n = grid.size();
    m = grid.front().size();
    this->grid = grid;
    int ans = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        ans = max(ans, dfs(i, j));
      }
    }

    return ans;
  }
};
