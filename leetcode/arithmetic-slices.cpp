#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int numberOfArithmeticSlices(const vector<int>& nums) {
    const int n = nums.size();
    if (n < 3) return 0;

    int ans = 0;
    int curr_diff = nums[0] - nums[1];

    int i = 0;

    for (int j = 0; j < n; j++) {
      if (j + 1 == n || nums[j] - nums[j + 1] != curr_diff) {
        const int k = j - i;
        ans += (k * (k - 1)) / 2;

        if (j + 1 != n) curr_diff = nums[j] - nums[j + 1];
        i = j;
      }
    }

    return ans;
  }
};
