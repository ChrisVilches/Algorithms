#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maximumJumps(const vector<int>& nums, const int target) {
    const int n = nums.size();
    vector<int> dp(n);
    dp.front() = -1;
    dp.back() = 0;

    for (int i = n - 2; i >= 0; i--) {
      for (int j = i + 1; j < n; j++) {
        if (j != n - 1 && dp[j] == 0) continue;

        if (abs(nums[j] - nums[i]) <= target) {
          dp[i] = max(dp[i], 1 + dp[j]);
        }
      }
    }

    return dp.front();
  }
};
