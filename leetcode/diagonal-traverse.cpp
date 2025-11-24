#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> findDiagonalOrder(const vector<vector<int>>& mat) {
    const int n = mat.size();
    const int m = mat.front().size();

    vector<int> ans;

    bool up = true;

    int i = 0;
    int j = 0;

    while (static_cast<int>(ans.size()) < n * m) {
      ans.emplace_back(mat[i][j]);

      if (up) {
        if (j == m - 1) {
          i++;
          up = false;
        } else if (i == 0) {
          j++;
          up = false;
        } else {
          i--;
          j++;
        }
      } else {
        if (i == n - 1) {
          j++;
          up = true;
        } else if (j == 0) {
          i++;
          up = true;
        } else {
          i++;
          j--;
        }
      }
    }

    return ans;
  }
};
