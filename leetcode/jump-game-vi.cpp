#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maxResult(vector<int>& nums, int k) {
    deque<int> d;
    d.push_back(nums.back());

    vector<int> dp(nums.size());
    dp.back() = nums.back();

    for (int i = nums.size() - 2; i >= 0; i--) {
      dp[i] = nums[i] + d.front();

      if (i + k < (int)dp.size()) {
        if (dp[i + k] == d.back())
          d.pop_back();
        else if (dp[i + k] == d.front())
          d.pop_front();
      }

      if (dp[i] > d.front()) {
        d.push_front(dp[i]);
      } else {
        while (!d.empty() && dp[i] > d.back()) d.pop_back();
        d.push_back(dp[i]);
      }
    }

    return dp[0];
  }
};
