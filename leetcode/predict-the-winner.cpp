#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<int> nums;
  int memo[21][21];
  bool ok[21][21];

  int dp(const int i, const int j) {
    if (i > j) return 0;
    if (ok[i][j]) return memo[i][j];

    const int first = nums[i] - dp(i + 1, j);
    const int last = nums[j] - dp(i, j - 1);
    ok[i][j] = true;
    return memo[i][j] = max(first, last);
  }

 public:
  bool predictTheWinner(const vector<int>& nums) {
    this->nums = nums;
    memset(ok, 0, sizeof ok);
    return dp(0, nums.size() - 1) >= 0;
  }
};
