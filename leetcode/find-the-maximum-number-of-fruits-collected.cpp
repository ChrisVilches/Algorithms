#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<vector<int>> matrix;
  int memo[1007][1007];
  int n;

  int dp(const int i, const int j) {
    if (i >= n || j >= n || i < 0 || j < 0) return 0;
    if (~memo[i][j]) return memo[i][j];

    int res = 0;

    if (i < j) {
      const int i2 = i + 1;
      for (const int j2 : {j - 1, j, j + 1}) {
        if (i2 < j2) res = max(res, dp(i2, j2));
      }
    } else {
      const int j2 = j + 1;
      for (const int i2 : {i - 1, i, i + 1}) {
        if (i2 > j2) res = max(res, dp(i2, j2));
      }
    }

    return memo[i][j] = matrix[i][j] + res;
  }

 public:
  int maxCollectedFruits(vector<vector<int>>& fruits) {
    memset(memo, -1, sizeof memo);
    this->matrix = fruits;
    this->n = matrix.size();

    int diagonal = 0;

    for (int i = 0; i < n; i++) {
      diagonal += matrix[i][i];
    }

    return diagonal + dp(n - 1, 0) + dp(0, n - 1);
  }
};
