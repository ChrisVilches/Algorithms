#include <bits/stdc++.h>
using namespace std;

class Solution {
  int dp[101][101];

 public:
  int uniquePaths(const int m, const int n) {
    dp[0][0] = 1;

    for (int i = 1; i < m; i++) dp[i][0] = 1;
    for (int i = 1; i < n; i++) dp[0][i] = 1;

    for (int i = 1; i < m; i++) {
      for (int j = 1; j < n; j++) {
        dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
      }
    }

    return dp[m - 1][n - 1];
  }
};
