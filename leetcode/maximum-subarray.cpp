#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maxSubArray(vector<int>& nums) {
    int ans = INT_MIN;
    int curr = 0;
    for (const int x : nums) {
      curr += x;
      ans = max(ans, curr);
      curr = max(curr, 0);
    }
    return ans;
  }
};
