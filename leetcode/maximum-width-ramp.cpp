#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maxWidthRamp(const vector<int>& nums) {
    const int n = nums.size();
    stack<int> s;

    for (int i = 0; i < n; i++) {
      if (s.empty() || nums[s.top()] > nums[i]) {
        s.emplace(i);
      }
    }

    int ans = 0;

    for (int i = n - 1; i >= 0; i--) {
      while (!s.empty() && nums[s.top()] <= nums[i]) {
        ans = max(ans, i - s.top());

        s.pop();
      }
    }

    return ans;
  }
};
