#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int numSpecial(const vector<vector<int>>& mat) {
    const int n = mat.size();
    const int m = mat.front().size();

    vector<int> rows(n, 0);
    vector<int> cols(m, 0);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        rows[i] += mat[i][j];
        cols[j] += mat[i][j];
      }
    }

    int ans = 0;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        ans += mat[i][j] == 1 && rows[i] == 1 && cols[j] == 1;
      }
    }

    return ans;
  }
};
