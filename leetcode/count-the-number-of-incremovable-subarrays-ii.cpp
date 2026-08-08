#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  long long incremovableSubarrayCount(vector<int>& nums) {
    const int n = nums.size();
    long long ans = n + (1LL * n * (n - 1)) / 2;

    int j = n - 1;

    for (; j > 0; j--) {
      if (nums[j - 1] >= nums[j]) break;
    }

    if (j == 0) return ans;

    vector<int> by_right(n, -1);

    by_right[j - 1] = 0;

    for (int i = 0; i < n; i++) {
      if (i != 0 && nums[i - 1] >= nums[i]) break;

      while (j < n && nums[i] >= nums[j]) j++;

      by_right[j - 1] = i + 1;
    }

    for (int i = 0, a = 0; i <= n; i++) {
      const long long b = (i == n ? n : by_right[i]);
      if (b == -1) continue;

      const long long x = (b - a + 1);

      ans += ((a + b) * x) / 2 - x * i;

      a = b + 1;
    }

    return ans;
  }
};
