#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int jump(vector<int>& nums) {
    const int n = nums.size();
    vector<int> dp(n, 1e9);
    dp.back() = 0;
    for (int i = n - 2; i >= 0; i--) {
      const int limit = min(i + nums[i] + 1, n);
      dp[i] = 1 + *min_element(dp.begin() + i, dp.begin() + limit);
    }
    return dp[0];
  }
};
