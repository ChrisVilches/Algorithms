#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int minimumTotal(const vector<vector<int>>& triangle) {
    const int n = triangle.size();

    vector<int> next = triangle.back();
    vector<int> curr(n);

    for (int i = n - 2; i >= 0; i--) {
      for (int j = 0; j <= i; j++) {
        curr[j] = triangle[i][j] + min(next[j], next[j + 1]);
      }

      curr.swap(next);
    }

    return next.front();
  }
};
