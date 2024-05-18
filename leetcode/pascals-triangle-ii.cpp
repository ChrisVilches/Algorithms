#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> getRow(int rowIndex) {
    const int n = rowIndex + 1;
    vector<vector<int>> result(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
      result[i][0] = 1;
      result[i][i] = 1;
    }

    for (int i = 2; i < n; i++) {
      for (int j = 1; j < n - 1; j++) {
        result[i][j] = result[i - 1][j] + result[i - 1][j - 1];
      }
    }

    return result[rowIndex];
  }
};
