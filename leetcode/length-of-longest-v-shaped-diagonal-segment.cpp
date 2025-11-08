#include <bits/stdc++.h>
using namespace std;

class Solution {
  int memo[507][507][2][4][2];
  vector<vector<int>> grid;
  int n, m;

  const array<pair<int, int>, 4> dirs{
      pair<int, int>{-1, -1},
      {-1, 1},
      {1, 1},
      {1, -1},
  };

  int dp(const int i, const int j, const int zero, const int dir_idx, const int turns) {
    if (i < 0 || j < 0 || i >= n || j >= m) return 0;
    if (zero && grid[i][j] != 0) return 0;
    if (!zero && grid[i][j] != 2) return 0;

    int& mem = memo[i][j][zero][dir_idx][turns];
    if (~mem) return mem;

    int res = 0;

    const auto [di, dj] = dirs[dir_idx];
    res = max(res, 1 + dp(i + di, j + dj, !zero, dir_idx, turns));

    if (turns == 1) {
      const int d = (dir_idx + 1) % 4;
      const auto [di1, dj1] = dirs[d];

      res = max(res, 1 + dp(i + di1, j + dj1, !zero, d, 0));
    }

    return mem = res;
  }

 public:
  int lenOfVDiagonal(const vector<vector<int>>& input) {
    memset(memo, -1, sizeof memo);
    this->grid = input;
    this->n = grid.size();
    this->m = grid.front().size();

    int ans = 0;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (grid[i][j] == 1) {
          for (int d = 0; d < 4; d++) {
            const auto [di, dj] = dirs[d];
            ans = max(ans, 1 + dp(i + di, j + dj, 0, d, 1));
          }
        }
      }
    }

    return ans;
  }
};
