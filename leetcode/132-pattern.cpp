#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool find132pattern(const vector<int>& nums) {
    const int n = nums.size();
    stack<int> lo, s;

    for (size_t i = 0; i < nums.size(); i++) {
      if (lo.empty() || nums[lo.top()] > nums[i]) {
        lo.emplace(i);
      }
    }

    for (int i = n - 1; i >= 1; i--) {
      if (i == lo.top()) lo.pop();

      while (!s.empty() && nums[i] > nums[s.top()]) {
        if (nums[lo.top()] < nums[s.top()]) {
          return true;
        }

        s.pop();
      }

      s.emplace(i);
    }

    return false;
  }
};
