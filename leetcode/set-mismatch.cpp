#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> findErrorNums(vector<int>& nums) {
    int twice, missing;

    const int n = nums.size();
    const int total_sum = accumulate(nums.begin(), nums.end(), 0);
    const int all = (n * (n + 1)) / 2;

    for (size_t i = 0; i < nums.size(); i++) {
      const int idx = abs(nums[i]) - 1;

      if (nums[idx] < 0) {
        twice = idx + 1;
      } else {
        nums[idx] = -nums[idx];
      }
    }

    missing = all - total_sum + twice;

    return {twice, missing};
  }
};
