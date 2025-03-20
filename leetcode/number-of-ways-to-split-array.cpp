#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int waysToSplitArray(const vector<int>& nums) {
    int ans = 0;

    const long long total = accumulate(nums.begin(), nums.end(), 0LL);

    long long left_sum = 0;

    for (size_t i = 0; i < nums.size() - 1; i++) {
      left_sum += nums[i];
      const long long right_sum = total - left_sum;
      ans += left_sum >= right_sum;
    }

    return ans;
  }
};
