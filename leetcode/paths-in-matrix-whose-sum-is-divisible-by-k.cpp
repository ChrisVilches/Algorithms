#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int numberOfPaths(const vector<vector<int>>& grid, const int k) {
    const int n = grid.size();
    const int m = grid.front().size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(k, 0)));

    dp[n - 1][m - 1][0] = 1;

    for (int i = n - 2; i >= 0; i--)
      for (int x = 0; x < k; x++)
        dp[i][m - 1][x] = dp[i + 1][m - 1][(grid[i][m - 1] + x) % k];

    for (int j = m - 2; j >= 0; j--)
      for (int x = 0; x < k; x++)
        dp[n - 1][j][x] = dp[n - 1][j + 1][(grid[n - 1][j] + x) % k];

    for (int i = n - 2; i >= 0; i--) {
      for (int j = m - 2; j >= 0; j--) {
        for (int x = 0; x < k; x++) {
          const int val = (grid[i][j] + x) % k;
          const long long sum = dp[i + 1][j][val] + dp[i][j + 1][val];
          dp[i][j][x] = sum % 1'000'000'007;
        }
      }
    }

    return dp[0][0][grid.back().back() % k];
  }
};
