#include <bits/stdc++.h>
using namespace std;

class Solution {
  int memo[57][57][57];
  vector<vector<int>> grid;
  bool reachable = false;
  int n;

  bool invalid(const int i, const int j) { return i >= n || j >= n || grid[i][j] == -1; }

  int dp(const int i, const int j, const int u) {
    if (~memo[i][j][u]) return memo[i][j][u];

    const int v = i + j - u;

    if (invalid(i, j) || invalid(u, v)) return INT_MIN;

    const int cherries = grid[i][j] + (grid[u][v] && (i != u || j != v));

    if (i == n - 1 && j == n - 1 && u == n - 1 && v == n - 1) {
      reachable = true;
      return cherries;
    }

    const array<int, 4> states{
        dp(i + 1, j, u),
        dp(i + 1, j, u + 1),
        dp(i, j + 1, u),
        dp(i, j + 1, u + 1),
    };

    return memo[i][j][u] = cherries + *max_element(states.begin(), states.end());
  }

 public:
  int cherryPickup(const vector<vector<int>>& grid) {
    this->grid = grid;
    this->n = grid.size();
    memset(memo, -1, sizeof memo);
    const int res = dp(0, 0, 0);

    if (!reachable) return 0;

    return res;
  }
};
