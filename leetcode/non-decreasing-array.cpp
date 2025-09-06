#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool checkPossibility(const vector<int>& nums) {
    vector<int> a = nums;
    vector<int> b = nums;

    for (size_t i = 1; i < nums.size(); i++) {
      if (nums[i - 1] <= nums[i]) continue;

      a[i - 1] = a[i];
      b[i] = b[i - 1];

      break;
    }

    return is_sorted(a.begin(), a.end()) || is_sorted(b.begin(), b.end());
  }
};
