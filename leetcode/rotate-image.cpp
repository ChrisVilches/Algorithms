#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  void rotate(vector<vector<int>>& matrix) {
    const int n = matrix.size();

    for (auto& row : matrix) {
      for (int& x : row) x += 1000;
    }

    const int bitmask = (1 << 13) - 1;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        matrix[j][n - i - 1] |= (matrix[i][j] & bitmask) << 15;
      }
    }

    for (auto& row : matrix) {
      for (int& x : row) x = x >> 15;
      for (int& x : row) x -= 1000;
    }
  }
};
