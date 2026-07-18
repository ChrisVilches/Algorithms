#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int findMin(const vector<int>& nums) {
    if (nums.front() < nums.back()) return nums.front();

    int ans = INT_MAX;

    int hi = (int)nums.size() - 1;
    for (; hi >= 0; hi--) {
      ans = min(ans, nums[hi]);
      if (nums[hi] != nums.back()) break;
    }

    if (hi == -1) {
      return nums.front();
    }

    int lo = 0;
    int last = nums[hi];

    while (lo < hi) {
      const int mid = (lo + hi) / 2;
      ans = min(ans, nums[mid]);

      if (nums[mid] >= last) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }

    return ans;
  }
};
