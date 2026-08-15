#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int singleNonDuplicate(const vector<int>& nums) {
    const int n = nums.size();

    if (n == 1) return nums.front();

    int lo = 0;
    int hi = (n / 2) - 1;

    while (lo <= hi) {
      const int mid = (lo + hi) / 2;

      if (nums[mid * 2] == nums[(mid * 2) + 1]) {
        lo = mid + 1;
      } else {
        hi = mid - 1;
      }
    }

    return nums[lo * 2];
  }
};
