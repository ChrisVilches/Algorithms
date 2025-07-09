#include <bits/stdc++.h>
using namespace std;

class Solution {
  int memo[1001][51];
  vector<int> nums;

  int dp(const size_t idx, const int k) {
    if (idx == nums.size() && k == 0) return INT_MIN;
    if (k <= 0) return INT_MAX;
    if (~memo[idx][k]) return memo[idx][k];

    int res = INT_MAX;
    int sum = 0;

    for (size_t i = idx; i < nums.size(); i++) {
      sum += nums[i];
      const int max_sum = max(sum, dp(i + 1, k - 1));
      res = min(res, max_sum);
    }

    return memo[idx][k] = res;
  }

 public:
  int splitArray(const vector<int>& input, const int k) {
    memset(memo, -1, sizeof memo);
    this->nums = input;
    return dp(0, k);
  }
};
