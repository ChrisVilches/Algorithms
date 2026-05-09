#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<int> nums, multipliers;
  int memo[301][301];

  int dp(const size_t i, const size_t k) {
    const size_t j = nums.size() - 1 - (k - i);
    if (k == multipliers.size()) return 0;
    if (~memo[i][k]) return memo[i][k];

    const int start = (nums[i] * multipliers[k]) + dp(i + 1, k + 1);
    const int end = (nums[j] * multipliers[k]) + dp(i, k + 1);

    return memo[i][k] = max(start, end);
  }

 public:
  int maximumScore(const vector<int>& nums_input, const vector<int>& multipliers_input) {
    this->nums = nums_input;
    this->multipliers = multipliers_input;
    memset(memo, -1, sizeof memo);

    return dp(0, 0);
  }
};
