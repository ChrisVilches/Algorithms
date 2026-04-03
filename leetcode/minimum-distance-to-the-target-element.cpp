#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int getMinDistance(const vector<int>& nums, const int target, const int start) {
    int ans = INT_MAX;

    for (int i = 0; i < static_cast<int>(nums.size()); i++) {
      if (nums[i] == target) {
        ans = min(ans, abs(start - i));
      }
    }

    return ans;
  }
};
