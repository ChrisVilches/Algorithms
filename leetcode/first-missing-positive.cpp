#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int firstMissingPositive(vector<int>& nums) {
    int k = 0;
    for (const int x : nums) {
      if (x > 0) nums[k++] = x;
    }

    for (int i = 0; i < k; i++) {
      const int x = abs(nums[i]) - 1;

      if (x >= k) continue;

      nums[x] = -abs(nums[x]);
    }

    for (int i = 0; i < k; i++) {
      if (nums[i] > 0) return i + 1;
    }

    return k + 1;
  }
};
