#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int findPeakElement(const vector<int>& nums) {
    const int n = nums.size();

    if (n == 1) return 0;
    if (nums[0] > nums[1]) return 0;
    if (nums[n - 2] < nums[n - 1]) return n - 1;

    int lo = 1;
    int hi = n - 1;

    while (lo < hi) {
      const int mid = (lo + hi) / 2;

      if (nums[mid - 1] < nums[mid] && nums[mid] > nums[mid + 1]) {
        return mid;
      }

      if (nums[mid - 1] > nums[mid]) {
        hi = mid;
      } else {
        lo = mid + 1;
      }
    }

    assert(false);
  }
};
