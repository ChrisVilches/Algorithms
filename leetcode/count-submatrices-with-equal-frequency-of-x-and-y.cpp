#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int numberOfSubmatrices(const vector<vector<char>>& grid) {
    const int n = grid.size();
    const int m = grid.front().size();

    vector<vector<complex<int>>> pref(n, vector<complex<int>>(m, {0, 0}));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        pref[i][j] = {grid[i][j] == 'X', grid[i][j] == 'Y'};

        if (j > 0) pref[i][j] += pref[i][j - 1];
        if (i > 0) pref[i][j] += pref[i - 1][j];
        if (i > 0 && j > 0) pref[i][j] -= pref[i - 1][j - 1];
      }
    }

    int ans = 0;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        const int x = pref[i][j].real();
        const int y = pref[i][j].imag();

        ans += x == y && x > 0;
      }
    }

    return ans;
  }
};
