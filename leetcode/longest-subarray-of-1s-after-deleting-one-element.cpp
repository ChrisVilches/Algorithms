#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int longestSubarray(const vector<int>& nums) {
    const int n = nums.size();

    vector<int> right(n);

    for (int i = n - 1, count = 0; i >= 0; i--) {
      count = nums[i] == 0 ? 0 : count + 1;
      right[i] = count;
    }

    right.emplace_back(0);

    int ans = 0;

    for (int i = 0, count = 0; i < n; i++) {
      ans = max(ans, count + right[i + 1]);

      count = nums[i] == 0 ? 0 : count + 1;
    }

    return ans;
  }
};
