#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int longestOnes(const vector<int>& nums, const int k) {
    const int n = nums.size();
    int ans = 0;

    for (int i = 0, j = 0, curr = 0; j < n; j++) {
      if (nums[j] == 0) curr++;

      while (curr > k && i <= j) {
        if (nums[i] == 0) curr--;
        i++;
      }

      ans = max(ans, j - i + 1);
    }

    return ans;
  }
};
