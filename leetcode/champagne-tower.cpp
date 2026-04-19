#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  double champagneTower(const int poured, const int query_row, const int query_glass) {
    const int rows = query_row + 1;
    vector<vector<double>> grid(rows, vector<double>(rows, 0));

    grid[0][0] = poured;

    for (int i = 0; i < rows - 1; i++) {
      for (int j = 0; j <= i; j++) {
        const double extra = grid[i][j] - 1;
        if (extra <= 0) continue;

        grid[i + 1][j] += extra / 2;
        grid[i + 1][j + 1] += extra / 2;
      }
    }

    return min(grid[query_row][query_glass], 1.0);
  }
};
