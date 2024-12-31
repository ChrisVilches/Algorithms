#include <bits/stdc++.h>
using namespace std;

class Solution {
  int memo[307][307];
  vector<int> nums;

  int dp(const int from, const int to) {
    if (from > to) return 0;
    if (~memo[from][to]) return memo[from][to];

    int res = 0;

    for (int i = from; i <= to; i++) {
      const int mult = nums[from - 1] * nums[i] * nums[to + 1];
      res = max(res, mult + dp(from, i - 1) + dp(i + 1, to));
    }

    return memo[from][to] = res;
  }

 public:
  int maxCoins(const vector<int>& input) {
    nums = input;
    nums.emplace_back(1);
    nums.insert(nums.begin(), 1);

    memset(memo, -1, sizeof memo);
    return dp(1, nums.size() - 2);
  }
};
