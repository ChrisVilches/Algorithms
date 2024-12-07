#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int threeSumClosest(vector<int>& nums, const int target) {
    sort(nums.begin(), nums.end());

    const int n = nums.size();

    int ans = 0;
    int diff = INT_MAX;

    for (int i = 0; i < n - 2; i++) {
      for (int j = i + 1; j < n - 1; j++) {
        const int complement = target - (nums[i] + nums[j]);
        const auto it = lower_bound(nums.begin() + j + 1, nums.end(), complement);
        int idx = it - nums.begin();

        for (int iter = 0; iter < 2; iter++, idx--) {
          if (idx <= j || idx >= n) continue;

          const int total = nums[i] + nums[j] + nums[idx];
          const int curr_diff = abs(target - total);
          if (curr_diff < diff) {
            diff = curr_diff;
            ans = total;
          }
        }
      }
    }

    return ans;
  }
};
