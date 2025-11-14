#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool kLengthApart(const vector<int>& nums, const int k) {
    const int n = nums.size();
    int prev = -1;

    for (int i = 0; i < n; i++) {
      if (nums[i] != 1) continue;

      if (prev != -1 && i - prev - 1 < k) {
        return false;
      }

      prev = i;
    }

    return true;
  }
};
