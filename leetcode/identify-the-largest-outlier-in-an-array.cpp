#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int getLargestOutlier(const vector<int>& nums) {
    const int total = accumulate(nums.begin(), nums.end(), 0);
    int ans = INT_MIN;

    unordered_map<int, int> freq;
    for (const int x : nums) freq[x]++;

    for (const int outlier : nums) {
      const int sum_without_outlier = total - outlier;
      if (sum_without_outlier % 2 != 0) continue;

      const int sum_elem = sum_without_outlier / 2;

      if (!freq.count(sum_elem)) continue;
      if (outlier == sum_elem && freq[outlier] == 1) continue;

      ans = max(ans, outlier);
    }

    return ans;
  }
};
