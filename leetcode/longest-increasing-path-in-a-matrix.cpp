#include <bits/stdc++.h>
using namespace std;

class Solution {
  int n, m;
  int memo[207][207];
  vector<vector<int>> matrix;
  const int di[4]{-1, 1, 0, 0};
  const int dj[4]{0, 0, -1, 1};

  int dp(const int i, const int j) {
    if (~memo[i][j]) return memo[i][j];
    const int curr = matrix[i][j];

    int res = 0;

    for (int d = 0; d < 4; d++) {
      const int i2 = i + di[d];
      const int j2 = j + dj[d];
      if (i2 < 0 || j2 < 0 || i2 >= n || j2 >= m) continue;
      if (matrix[i2][j2] <= curr) continue;
      res = max(res, dp(i2, j2));
    }

    return memo[i][j] = 1 + res;
  }

 public:
  int longestIncreasingPath(const vector<vector<int>>& matrix) {
    memset(memo, -1, sizeof memo);
    n = matrix.size();
    m = matrix.front().size();
    this->matrix = matrix;

    int ans = 0;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        ans = max(ans, dp(i, j));
      }
    }

    return ans;
  }
};
