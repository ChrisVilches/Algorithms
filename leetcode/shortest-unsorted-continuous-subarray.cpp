#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int findUnsortedSubarray(const vector<int>& nums) {
    if (is_sorted(nums.begin(), nums.end())) return 0;

    size_t lo = INT_MAX;
    size_t hi;

    for (size_t i = 0; i < nums.size() - 1; i++) {
      if (lo == INT_MAX && nums[i] > nums[i + 1]) lo = i;
      if (nums[i] > nums[i + 1]) hi = i + 1;
    }

    int max_val = *max_element(nums.begin() + lo, nums.begin() + hi + 1);
    int min_val = *min_element(nums.begin() + lo, nums.begin() + hi + 1);

    while (lo > 0 && nums[lo - 1] > min_val) {
      min_val = min(min_val, nums[--lo]);
    }

    while (hi < nums.size() - 1 && nums[hi + 1] < max_val) {
      max_val = max(max_val, nums[++hi]);
    }

    return hi - lo + 1;
  }
};
