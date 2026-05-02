#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<int> nums;
  int memo[3][40'007];

  int dp(const size_t idx, const int mod) {
    if (idx == nums.size()) return mod == 0 ? 0 : INT_MIN;
    if (~memo[mod][idx]) return memo[mod][idx];

    return memo[mod][idx] = max({
               nums[idx] + dp(idx + 1, (nums[idx] + mod) % 3),
               dp(idx + 1, mod),
           });
  }

 public:
  int maxSumDivThree(const vector<int>& input) {
    memset(memo, -1, sizeof memo);
    this->nums = input;
    return dp(0, 0);
  }
};
