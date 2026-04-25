#include <bits/stdc++.h>
using namespace std;

class Solution {
  int dp[307][307];

 public:
  int countSquares(const vector<vector<int>>& matrix) {
    const int n = matrix.size();
    const int m = matrix.front().size();

    memset(dp, 0, sizeof dp);

    for (int i = 0; i < n; i++) dp[i][0] = matrix[i][0];
    for (int i = 0; i < m; i++) dp[0][i] = matrix[0][i];

    for (int i = 1; i < n; i++) {
      for (int j = 1; j < m; j++) {
        if (matrix[i][j] == 0) continue;

        dp[i][j] = 1 + min({dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]});
      }
    }

    int ans = 0;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        ans += dp[i][j];
      }
    }

    return ans;
  }
};
