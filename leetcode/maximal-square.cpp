#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maximalSquare(const vector<vector<char>>& matrix) {
    const int n = matrix.size();
    const int m = matrix.front().size();
    vector<vector<int>> dp(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++) dp[i][0] = matrix[i][0] == '1';
    for (int i = 0; i < m; i++) dp[0][i] = matrix[0][i] == '1';

    for (int i = 1; i < n; i++) {
      for (int j = 1; j < m; j++) {
        if (matrix[i][j] == '1') {
          dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
        }
      }
    }

    int ans = 0;

    for (const vector<int>& row : dp) {
      for (const int x : row) ans = max(ans, x * x);
    }

    return ans;
  }
};
