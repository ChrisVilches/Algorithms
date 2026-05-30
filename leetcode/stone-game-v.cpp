#include <bits/stdc++.h>
using namespace std;

// TODO: Got WA when re-submitting (presumably due to newly added tests).

class Solution {
  vector<int> nums;
  int memo[507][507];

  int dp(const int l, const int r) {
    if (l == r) return 0;
    if (~memo[l][r]) return memo[l][r];

    const int total = accumulate(nums.begin() + l, nums.begin() + r + 1, 0);

    int res = 0;
    int left = 0;

    for (int i = l; i < r; i++) {
      left += nums[i];
      const int right = total - left;

      const int left_value = left + dp(l, i);
      const int right_value = right + dp(i + 1, r);

      if (left == right) {
        res = max(left_value, right_value);
      } else if (left > right) {
        res = max(res, right_value);
      } else {
        res = max(res, left_value);
      }
    }

    return memo[l][r] = res;
  }

 public:
  int stoneGameV(const vector<int>& stoneValue) {
    memset(memo, -1, sizeof memo);
    nums = stoneValue;
    return dp(0, stoneValue.size() - 1);
  }
};
