#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int minimumArea(const vector<vector<int>>& grid) {
    const int n = grid.size();
    const int m = grid.front().size();

    int i1 = INT_MAX;
    int i2 = INT_MIN;
    int j1 = INT_MAX;
    int j2 = INT_MIN;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (grid[i][j] != 1) continue;

        i1 = min(i1, i);
        i2 = max(i2, i);
        j1 = min(j1, j);
        j2 = max(j2, j);
      }
    }

    return (j2 - j1 + 1) * (i2 - i1 + 1);
  }
};
