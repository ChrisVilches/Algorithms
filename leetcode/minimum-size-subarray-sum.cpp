#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int minSubArrayLen(const int target, const vector<int>& nums) {
    size_t ans = INT_MAX;
    int curr = 0;

    for (size_t i = 0, j = 0; j < nums.size(); j++) {
      curr += nums[j];

      while (curr >= target) {
        ans = min(ans, j - i + 1);
        curr -= nums[i++];
      }
    }

    return ans == INT_MAX ? 0 : ans;
  }
};
