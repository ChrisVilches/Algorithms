#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> searchRange(vector<int>& nums, int target) {
    if (!binary_search(nums.begin(), nums.end(), target)) {
      return {-1, -1};
    }

    const int a = lower_bound(nums.begin(), nums.end(), target) - nums.begin();
    const int b = upper_bound(nums.begin(), nums.end(), target) - nums.begin() - 1;
    return {a, b};
  }
};
