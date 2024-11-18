#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maximumTop(const vector<int>& nums, const int k) {
    const int n = nums.size();

    if (k == 0) return nums.front();

    if (n == 1 && k % 2 == 1) return -1;

    if (k == 1) return nums[1];

    if (k < n) {
      return max(nums[k], *max_element(nums.begin(), nums.begin() + k - 1));
    }

    if (k == n) {
      return *max_element(nums.begin(), nums.begin() + k - 1);
    }

    return *max_element(nums.begin(), nums.end());
  }
};
