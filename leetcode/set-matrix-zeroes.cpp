#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  void setZeroes(vector<vector<int>>& matrix) {
    const int n = matrix.size();
    const int m = matrix.front().size();

    const auto contains = [&](const int x) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          if (matrix[i][j] == x) return true;
        }
      }
      return false;
    };

    int x;
    while (true) {
      x = rand();
      if (!contains(x)) break;
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (matrix[i][j] != 0) continue;

        for (int k = 0; k < m; k++) {
          if (matrix[i][k] != 0) matrix[i][k] = x;
        }
        for (int k = 0; k < n; k++) {
          if (matrix[k][j] != 0) matrix[k][j] = x;
        }
      }
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (matrix[i][j] == x) {
          matrix[i][j] = 0;
        }
      }
    }
  }
};
