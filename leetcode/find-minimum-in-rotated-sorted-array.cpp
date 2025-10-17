#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int findMin(const vector<int>& nums) {
    const int n = nums.size();
    int lo = 0;
    int hi = n;

    while (lo < hi) {
      const int mid = (lo + hi) / 2;
      if (nums[mid] >= nums.front()) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }

    if (lo == n) return nums.front();
    return nums[lo];
  }
};
