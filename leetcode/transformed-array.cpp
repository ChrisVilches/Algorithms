#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> constructTransformedArray(const vector<int>& nums) {
    const int n = nums.size();
    vector<int> res(nums.size());

    for (int i = 0; i < n; i++) {
      if (nums[i] == 0) {
        res[i] = nums[i];
        continue;
      }

      if (nums[i] > 0) {
        const int idx = (i + nums[i]) % n;
        res[i] = nums[idx];
        continue;
      }

      int idx = (i - abs(nums[i]));
      while (idx < 0) idx += n;
      idx %= n;
      res[i] = nums[idx];
    }

    return res;
  }
};
