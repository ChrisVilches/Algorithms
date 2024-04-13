#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int search(vector<int>& nums, int target) {
    const int lower = nums.back();

    int lo = 0;
    int hi = nums.size();

    while (lo < hi) {
      const int mid = (lo + hi) / 2;
      const int mid_val = nums[mid];

      if (mid_val > lower) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }

    const vector<int>::iterator hi_it = nums.begin() + hi;
    const vector<pair<vector<int>::iterator, vector<int>::iterator>> ranges{
        {hi_it, nums.end()}, {nums.begin(), hi_it}};

    for (const auto& [from, to] : ranges) {
      const auto result = lower_bound(from, to, target);
      if (result == to || *result != target) continue;

      return result - nums.begin();
    }

    return -1;
  }
};
