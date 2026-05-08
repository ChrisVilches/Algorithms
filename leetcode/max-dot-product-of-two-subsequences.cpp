#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<int> A, B;
  int memo[507][507][2];
  int n, m;

  int dp(const int i, const int j, const bool used) {
    if (i >= n || j >= m) return used ? 0 : INT_MIN;
    if (memo[i][j][used] != INT_MAX) return memo[i][j][used];

    const int not_use = dp(i + 1, j, used);
    int use = INT_MIN;

    for (int k = j; k < m; k++) {
      const int dot = A[i] * B[k];
      const int other = dp(i + 1, k + 1, true);

      if (other == INT_MIN) {
        use = max(use, dot);
      } else {
        use = max(use, dot + other);
      }
    }

    return memo[i][j][used] = max(not_use, use);
  }

 public:
  int maxDotProduct(const vector<int>& nums1, const vector<int>& nums2) {
    this->A = nums1;
    this->B = nums2;
    this->n = nums1.size();
    this->m = nums2.size();

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        memo[i][j][0] = INT_MAX;
        memo[i][j][1] = INT_MAX;
      }
    }

    return dp(0, 0, false);
  }
};
