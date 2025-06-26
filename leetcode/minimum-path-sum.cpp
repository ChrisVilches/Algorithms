#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int minPathSum(const vector<vector<int>>& grid) {
    const int n = grid.size();
    const int m = grid.front().size();
    vector<vector<int>> dp(n, vector<int>(m));

    dp.back().back() = grid.back().back();

    for (int i = m - 2; i >= 0; i--) dp.back()[i] = grid.back()[i] + dp.back()[i + 1];
    for (int i = n - 2; i >= 0; i--) dp[i].back() = grid[i].back() + dp[i + 1].back();

    for (int i = n - 2; i >= 0; i--) {
      for (int j = m - 2; j >= 0; j--) {
        const int cost = grid[i][j];
        dp[i][j] = min(cost + dp[i + 1][j], cost + dp[i][j + 1]);
      }
    }

    return dp.front().front();
  }
};
