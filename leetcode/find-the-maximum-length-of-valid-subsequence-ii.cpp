#include <bits/stdc++.h>
using namespace std;

class Solution {
  int dp[1003][1003];

 public:
  int maximumLength(const vector<int>& nums, const int k) {
    const int n = nums.size();
    memset(dp, -1, sizeof dp);

    int ans = 0;

    for (int i = n - 2; i >= 0; i--) {
      for (int j = i + 1; j < n; j++) {
        const int sum = (nums[i] + nums[j]) % k;
        const int val = dp[j][sum] != -1 ? 1 + dp[j][sum] : 2;

        ans = max(ans, val);
        dp[i][sum] = max(dp[i][sum], val);
      }
    }

    return ans;
  }
};
