#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> leftRightDifference(const vector<int>& nums) {
    vector<int> ans;

    int sum = 0;

    for (const int x : nums) {
      ans.emplace_back(sum);
      sum += x;
    }

    sum = 0;

    for (size_t i = nums.size(); i-- > 0;) {
      ans[i] = abs(ans[i] - sum);
      sum += nums[i];
    }

    return ans;
  }
};
