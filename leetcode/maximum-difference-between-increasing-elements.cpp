#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maximumDifference(const vector<int>& nums) {
    const int n = nums.size();
    vector<int> mx(n);
    mx.back() = nums.back();

    for (int i = n - 2; i >= 0; i--) {
      mx[i] = max(nums[i], mx[i + 1]);
    }

    int ans = 0;

    for (int i = 0; i < n - 1; i++) {
      ans = max(ans, mx[i + 1] - nums[i]);
    }

    return ans == 0 ? -1 : ans;
  }
};
