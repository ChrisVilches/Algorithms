#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int numSubarrayProductLessThanK(const vector<int>& nums, const int k) {
    if (k <= 1) return 0;

    int ans = 0;
    int curr = 1;

    for (size_t i = 0, j = 0; j < nums.size(); j++) {
      curr *= nums[j];

      while (curr >= k) {
        curr /= nums[i++];
      }

      ans += j - i + 1;
    }

    return ans;
  }
};
