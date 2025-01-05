#include <bits/stdc++.h>
using namespace std;

class Solution {
  long long dp[107][107];

 public:
  int uniquePathsWithObstacles(const vector<vector<int>>& grid) {
    const int n = grid.size();
    const int m = grid.front().size();

    if (grid[n - 1][m - 1] == 1) return 0;

    memset(dp, 0, sizeof dp);

    dp[n - 1][m - 1] = 1;

    for (int j = m - 2; j >= 0; j--) {
      if (grid[n - 1][j] == 1) break;
      dp[n - 1][j] = dp[n - 1][j + 1];
    }

    for (int i = n - 2; i >= 0; i--) {
      if (grid[i][m - 1] == 1) break;
      dp[i][m - 1] = dp[i + 1][m - 1];
    }

    for (int i = n - 2; i >= 0; i--) {
      for (int j = m - 2; j >= 0; j--) {
        if (grid[i][j] == 1) continue;

        dp[i][j] = dp[i + 1][j] + dp[i][j + 1];
      }
    }

    return dp[0][0];
  }
};
