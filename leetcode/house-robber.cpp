#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<int> nums, memo;

  int dp(const int i) {
    if (i >= (int)nums.size()) return 0;
    if (~memo[i]) return memo[i];

    return memo[i] = max(nums[i] + dp(i + 2), dp(i + 1));
  }

 public:
  int rob(const vector<int>& nums) {
    memo = vector<int>(nums.size(), -1);
    this->nums = nums;
    return dp(0);
  }
};
