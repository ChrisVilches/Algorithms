#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<vector<int>> grid;
  int memo[501][501][3];
  const int INF = 100'000'000;

  int dp(const int i, const int j, const int defense) {
    const int n = grid.size();
    const int m = grid.front().size();
    if (defense < 0) return -INF;
    if (i == n - 1 && j == m) return INF;
    if (i == n || j == m) return 0;
    if (~memo[i][j][defense]) return memo[i][j][defense];

    return memo[i][j][defense] = max({
               dp(i + 1, j, defense - 1),
               dp(i, j + 1, defense - 1),
               grid[i][j] + dp(i + 1, j, defense),
               grid[i][j] + dp(i, j + 1, defense),
           });
  }

 public:
  int maximumAmount(const vector<vector<int>>& coins) {
    this->grid = coins;
    memset(memo, -1, sizeof memo);
    return dp(0, 0, 2) - INF;
  }
};
