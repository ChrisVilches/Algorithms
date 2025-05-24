#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int projectionArea(const vector<vector<int>>& grid) {
    const int n = grid.size();
    const int m = grid.front().size();
    int ans = 0;

    for (const auto& row : grid) {
      ans += *max_element(row.begin(), row.end());
    }

    for (int j = 0; j < m; j++) {
      int h = 0;
      for (int i = 0; i < n; i++) {
        h = max(h, grid[i][j]);
        ans += grid[i][j] > 0;
      }
      ans += h;
    }

    return ans;
  }
};
