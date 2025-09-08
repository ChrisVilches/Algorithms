#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  double findMaxAverage(const vector<int>& nums, const int k) {
    int curr = accumulate(nums.begin(), nums.begin() + k, 0);
    int ans = curr;

    for (size_t i = 0; i < nums.size() - k; i++) {
      curr -= nums[i];
      curr += nums[i + k];

      ans = max(ans, curr);
    }

    return ans / static_cast<double>(k);
  }
};
