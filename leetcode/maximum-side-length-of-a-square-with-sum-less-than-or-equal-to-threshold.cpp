#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maxSideLength(const vector<vector<int>>& mat, const int threshold) {
    const int n = mat.size();
    const int m = mat.front().size();

    vector<vector<int>> pref(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        pref[i][j] =
            mat[i - 1][j - 1] + pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
      }
    }

    const auto range_sum = [&](const int i, const int j, const int side) {
      const int i2 = i + side + 1;
      const int j2 = j + side + 1;

      return pref[i2][j2] - pref[i][j2] - pref[i2][j] + pref[i][j];
    };

    int ans = 0;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        int lo = 0;
        int hi = min(n - i, m - j);

        while (lo < hi) {
          const int mid = (lo + hi) / 2;

          if (range_sum(i, j, mid) <= threshold) {
            lo = mid + 1;
          } else {
            hi = mid;
          }
        }

        ans = max(ans, lo);
      }
    }

    return ans;
  }
};
